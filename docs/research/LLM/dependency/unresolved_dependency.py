import re
import os
import json
from pathlib import Path

def extract_dependencies(model_output):
    dependencies = [dep.strip() for dep in model_output.split(',') if dep.strip()]
    
    return dependencies if dependencies else None
    #return all unresolved dependencies

def extract_braced_function(lines, start_line_index=0):
    """辅助函数：基于大括号的函数提取"""
    function_lines = []
    brace_count = 0
    end_line = start_line_index
    
    # 处理可能的首行
    first_line = lines[0] if lines else ""
    function_lines.append(first_line)
    brace_count += first_line.count('{') - first_line.count('}')
    end_line += 1
    
    # 如果没有找到开括号，继续查找
    if brace_count == 0:
        for line in lines[1:]:
            function_lines.append(line)
            brace_count += line.count('{') - line.count('}')
            end_line += 1
            if brace_count > 0:
                break
    
    # 如果找到开括号，继续直到匹配闭括号
    if brace_count > 0:
        for line in lines[len(function_lines):]:
            function_lines.append(line)
            brace_count += line.count('{') - line.count('}')
            end_line += 1
            if brace_count == 0:
                break
    
    return '\n'.join(function_lines), end_line

def extract_function_body(content, start_pos, base_indent, file_ext):
    lines = content[start_pos:].split('\n')
    function_lines = []
    end_line = content[:start_pos].count('\n') + 1
    
    if file_ext == '.py':
        # Python函数提取 - 基于缩进规则
        first_line = lines[0]
        function_lines.append(first_line)
        current_indent = base_indent
        
        for line in lines[1:]:
            stripped = line.lstrip()
            line_indent = len(line) - len(stripped)
            
            # 检查是否遇到下一个def/class或缩进小于等于函数定义
            if stripped.startswith(('def ', 'class ')) and line_indent <= current_indent:
                break
                
            # 检查空行或注释行（保持包含）
            if not stripped or stripped.startswith('#'):
                function_lines.append(line)
                end_line += 1
                continue
                
            # 检查是否仍在函数体内
            if line_indent > current_indent:
                function_lines.append(line)
                end_line += 1
            else:
                break
        return function_lines
    
    elif file_ext in ('.js', '.ts', '.jsx', '.tsx', '.c', '.cpp', '.h', '.hpp', '.java', '.rs'):
        # 处理所有基于大括号的语言
        function_body, _ = extract_braced_function(lines)
        return function_body
    
    else:
        return "language not supported"

def search_function_in_repo(project_path, function_name):
    if not os.path.isdir(project_path):
        raise ValueError(f"路径 '{project_path}' 不是一个有效的目录")
    
    results = {
        'function_name': function_name,
        'matches': [],
        'total_matches': 0
    }

    # 定义各语言的函数匹配模式
    patterns = {
        # Python: def function_name(...):
        '.py': re.compile(
            r'^(\s*)def\s+' + re.escape(function_name) + r'\s*\(.*\)\s*:\s*$',
            re.MULTILINE
        ),
        # JavaScript/TypeScript: function function_name(...) {
        '.js': re.compile(
            r'^(?:\s*(?:export\s+|async\s+)*function\s+' + re.escape(function_name) + 
            r'\s*\(.*\)\s*{|' +
            r'\s*(?:export\s+|async\s+)*const\s+' + re.escape(function_name) + 
            r'\s*=\s*(?:async\s*)?\(.*\)\s*=>\s*{|' +
            r'\s*(?:export\s+)?let\s+' + re.escape(function_name) + 
            r'\s*=\s*(?:async\s*)?\(.*\)\s*=>\s*{|' +
            r'\s*(?:export\s+)?var\s+' + re.escape(function_name) + 
            r'\s*=\s*(?:async\s*)?\(.*\)\s*=>\s*{)',
            re.MULTILINE
        ),
        # C/C++: [return_type] function_name(...) {
        '.c': re.compile(
            r'^(?:\s*(?:\w+\s+)*\w+\s+)?' + re.escape(function_name) + 
            r'\s*\([^;]*\)\s*(?:\s*\w+\s*)*\s*\{',
            re.MULTILINE
        ),
        '.cpp': re.compile(
            r'^(?:\s*(?:\w+\s+)*\w+\s+)?' + re.escape(function_name) + 
            r'\s*\([^;]*\)\s*(?:\s*\w+\s*)*\s*\{',
            re.MULTILINE
        ),
        '.h': re.compile(
            r'^(?:\s*(?:\w+\s+)*\w+\s+)?' + re.escape(function_name) + 
            r'\s*\([^;]*\)\s*(?:\s*\w+\s*)*\s*\{',
            re.MULTILINE
        ),
        # Java: [modifiers] return_type function_name(...) {
        '.java': re.compile(
            r'^\s*(?:[a-zA-Z_][\w\.\[\]]+\s+)*' + re.escape(function_name) + 
            r'\s*\([^;]*\)\s*(?:throws\s+[\w\.,\s]+)?\s*\{',
            re.MULTILINE
        ),
        # Rust: fn function_name(...) {
        '.rs': re.compile(
            r'^\s*(?:pub\s+)?(?:unsafe\s+)?fn\s+' + re.escape(function_name) + 
            r'\s*\([^;]*\)\s*(?:->\s*[^{;]+)?\s*\{',
            re.MULTILINE
        )
    }

    # 需要处理的文件扩展名
    supported_extensions = set(patterns.keys())
    
    # 忽略的目录
    ignored_dirs = {'.git', 'node_modules', 'venv', '__pycache__', 'target', 'build'}

    # 遍历仓库目录
    for root, dirs, files in os.walk(project_path):
        # 移除忽略的目录
        dirs[:] = [d for d in dirs if d not in ignored_dirs]
        
        for file in files:
            file_path = os.path.join(root, file)
            _, ext = os.path.splitext(file)
            
            if ext.lower() not in supported_extensions:
                continue
                
            try:
                with open(file_path, 'r', encoding='utf-8') as f:
                    content = f.read()
                    pattern = patterns[ext.lower()]
                    matches = pattern.finditer(content)
                    
                    for match in matches:
                        start_line = content[:match.start()].count('\n') + 1
                        indent = len(match.group(1)) if ext == '.py' and match.groups() else 0
                        
                        # 获取整个函数体
                        function_content = extract_function_body(
                            content, 
                            match.start(), 
                            indent, 
                            ext
                        )
                        
                        results['matches'].append({
                            'file_path': file_path,
                            'start_line': start_line,
                            'content': function_content
                        })
                        results['total_matches'] += 1
                        
            except (UnicodeDecodeError, PermissionError) as e:
                print(f"无法读取文件 {file_path}: {str(e)}")
                continue
    
    return results

def main(model_output, project_path):
    """receive model output and project path, return JSON with found dependencies"""
    dependencies = extract_dependencies(model_output)
    if not dependencies:
        return json.dumps({
            "status": "failed",
            "message": "No dependencies extracted",
            "results": []
        }, indent=2)
    
    results = []
    found_deps = set()
    for dep in dependencies:
        result = search_function_in_repo(project_path, dep)
        results.append(result)
        if result['total_matches'] > 0:
            found_deps.add(dep)
    missing_deps = [dep for dep in dependencies if dep not in found_deps]
    
    return json.dumps({
        "status": "success" if not missing_deps else "partial",
        "dependencies_searched": dependencies,
        "dependencies_found": results,
        "dependencies_missing": missing_deps,
        "message": f"Found {len(results)}/{len(dependencies)} dependencies"
    }, indent=2)
