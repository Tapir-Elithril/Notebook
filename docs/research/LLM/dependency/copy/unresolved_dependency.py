import re
import json
from pathlib import Path
from fuzzywuzzy import fuzz,process

DEPENDENCY_FILES = {
    "java": ["pom.xml", "build.gradle", "*.gradle.kts"],
    "python": ["requirements.txt", "setup.py", "pyproject.toml"],
    "js": ["package.json"],
    "cpp": ["CMakeLists.txt", "Makefile", "*.cmake"]
}

def case_insensitive_file_exists(path, filename_pattern):
    """check if a file matching the pattern exists in the directory, case-insensitive"""
    pattern = re.compile(filename_pattern, re.IGNORECASE)
    for file in path.iterdir():
        if pattern.fullmatch(file.name):
            return True
    return False

def detect_project_type(project_path):
    """support multiple languages, detect project type based on file existence"""
    path = Path(project_path)
    detected_langs = []
    
    if any(case_insensitive_file_exists(path, f) for f in ["pom.xml", "build.gradle", r".*\.gradle.kts"]):
        detected_langs.append("java")
    if any(case_insensitive_file_exists(path, f) for f in ["requirements.txt", "setup.py", "pyproject.toml"]):
        detected_langs.append("python")
    if any(case_insensitive_file_exists(path, f) for f in ["package.json"]):
        detected_langs.append("js")
    if any(case_insensitive_file_exists(path, f) for f in ["CMakeLists.txt", "Makefile", r".*\.cmake"]):
        detected_langs.append("cpp")
    
    return detected_langs if detected_langs else ["unknown_language"]

def extract_dependencies(model_output):
    """extract dependencies from model output using regex"""
    patterns = [
        r"(?:unresolved|could not resolve|missing|failed to resolve|could not find)\s*:?(?:\s*dependency\s*[: ]?)?\s*([a-zA-Z0-9\-_.]+:[a-zA-Z0-9\-_.]+|[a-zA-Z0-9\-_.]+)",
        # Python
        r"ModuleNotFoundError: No module named [\"']([a-zA-Z0-9\-_.]+)[\"']",
        # pip
        r"ERROR: Could not find a version that satisfies the requirement ([a-zA-Z0-9\-_.]+(?:\s*[><=!]=\s*[0-9.]+)?)",
        # NPM
        r"npm ERR! 404 Not Found: ([a-zA-Z0-9\-_.]+)@",
        # package
        r"package [\"']([a-zA-Z0-9\-_.]+)[\"'] is not found"
    ]
    
    combined_pattern = re.compile("|".join(patterns), re.IGNORECASE)

    dependencies = []
    for match in combined_pattern.finditer(model_output):
        dep = next((g for g in match.groups() if g is not None), None)
        if dep:
            dep = re.sub(r"\s*([><=!]+)\s*", r"\1", dep.strip())
            dependencies.append(dep)

    return dependencies if dependencies else None
    #return all unresolved dependencies

def find_dependencies(project_path, dependencies, fuzzy_threshold=80):
    """search for dependencies in batch"""
    project_type = detect_project_type(project_path)
    files = []
    for project_type in project_type:
        files += DEPENDENCY_FILES.get(project_type, [])
    results = []
    
    for file in files:
        path = Path(project_path) / file
        if not path.exists():
            continue
            
        try:
            with open(path, 'r', encoding='utf-8') as f:
                lines = [(i, line.strip()) for i, line in enumerate(f.readlines(), 1) 
                    if line.strip() and not line.lstrip().startswith(('#', '//'))] # neglect comments
        except UnicodeDecodeError:
            continue
        
        for dependency in dependencies:
        #     # 1. find declaration in build files (e.g., Maven/Gradle)
        #     build_declaration = search_build_files(project_path, dep)
        #     if build_declaration:
        #         yield {
        #             **build_declaration,
        #             "resolution_hint": generate_resolution_hint(dep, build_declaration)
        #         }
            
        #     # 2. add runtime dependency analysis for python/java
        #     if is_runtime_dependency(dep):
        #         runtime_info = analyze_runtime_usage(project_path, dep)
        #         if runtime_info:
        #             yield runtime_info
            exact_match_found = False
            line_content_cache = [line[1] for line in lines]
            
            # 1. precise match
            for line_num, line in lines:
                if dependency in line:
                    results.append({
                        "dependency": dependency,
                        "found_in": str(path),
                        "file_type": file,
                        "match_type": "exact",
                        "matched_line": line,
                        "line_number": line_num
                    })
                    exact_match_found = True
                    break
            
            # 2. fuzzy match
            if not exact_match_found and line_content_cache:
                # 2.1quick select relevant lines based on tokens
                tokens = re.split(r"[:=\s\-]", dependency)
                candidate_lines = [
                    (line_num, line) for line_num, line in lines
                    if all(token in line for token in tokens if len(token) > 3)
                ]
                
                if not candidate_lines:
                    candidate_lines = lines
                
                #2.2 fuzzy match using fuzzywuzzy
                best_match = process.extractOne(
                    dependency,
                    [line for _, line in candidate_lines],
                    scorer=fuzz.partial_ratio
                )
                
                if best_match and best_match[1] >= fuzzy_threshold:
                    # find match line number
                    matched_line_num = candidate_lines[best_match[2]][0] if len(best_match) > 2 else None
                    results.append({
                        "dependency": dependency,
                        "found_in": str(path),
                        "file_type": file,
                        "match_type": "fuzzy",
                        "confidence": best_match[1],
                        "matched_line": best_match[0],
                        "line_number": matched_line_num
                    })
    
    return results

def print_dependency_file_content(results):
    """Read and print the content of files where dependencies are found."""
    for result in results:
        # get file path
        file_path = result.get("found_in")
        
        # check file path
        if file_path and Path(file_path).exists():
            with open(file_path, 'r', encoding='utf-8') as file:
                file_content = file.read()
                print(f"Content of file {file_path}:\n")
                print(file_content)
                print("-" * 50) 
        else:
            print(f"File {file_path} not found or invalid.")
    return 

def main(model_output, project_path):
    """receive model output and project path, return JSON with found dependencies"""
    dependencies = extract_dependencies(model_output)
    if not dependencies:
        return json.dumps({
            "status": "failed",
            "message": "No dependencies extracted",
            "results": []
        }, indent=2)
    
    results = find_dependencies(project_path, dependencies)
    
    found_deps = {res["dependency"] for res in results}
    missing_deps = [dep for dep in dependencies if dep not in found_deps]
    
    print_dependency_file_content(results)
    return json.dumps({
        "status": "success" if not missing_deps else "partial",
        "dependencies_searched": dependencies,
        "dependencies_found": results,
        "dependencies_missing": missing_deps,
        "message": f"Found {len(results)}/{len(dependencies)} dependencies"
    }, indent=2)
