import pytest
import os
import json
from tempfile import TemporaryDirectory
from pathlib import Path
from unresolved_dependency import *

# Test extract_dependencies function
def test_extract_dependencies():
    # Test with valid comma-separated dependencies
    assert extract_dependencies("dep1, dep2, dep3") == ["dep1", "dep2", "dep3"]
    assert extract_dependencies("  dep1  , dep2  ,  dep3  ") == ["dep1", "dep2", "dep3"]
    
    # Test with empty string
    assert extract_dependencies("") is None
    
    # Test with whitespace only
    assert extract_dependencies("   ") is None
    
    # Test with single dependency
    assert extract_dependencies("single_dep") == ["single_dep"]

# Test extract_braced_function function
def test_extract_braced_function():
    # Test with simple JavaScript function
    js_code = [
        "function test() {",
        "  console.log('test');",
        "}"
    ]
    result, end_line = extract_braced_function(js_code)
    assert result == "\n".join(js_code)
    assert end_line == 3
    
    # Test with nested braces
    nested_code = [
        "function test() {",
        "  if (true) {",
        "    console.log('nested');",
        "  }",
        "}"
    ]
    result, end_line = extract_braced_function(nested_code)
    assert result == "\n".join(nested_code)
    assert end_line == 5
    
    # Test with no opening brace on first line
    split_code = [
        "function test()",
        "{",
        "  return 1;",
        "}"
    ]
    result, end_line = extract_braced_function(split_code)
    assert result == "\n".join(split_code)
    assert end_line == 4

# Test extract_function_body function
def test_extract_function_body():
    # Test Python function
    # py_code = """def test():
    # print('hello')
    # return 42"""
    # result = extract_function_body(py_code, 0, 0, '.py')
    # assert result == py_code
    
    # Test JavaScript function
    js_code = """function test() {
    console.log('test');
}"""
    result = extract_function_body(js_code, 0, 0, '.js')
    assert result == js_code
    
    # Test unsupported language
    result = extract_function_body("some code", 0, 0, '.txt')
    assert result == "language not supported"

# Test search_function_in_repo function
def test_search_function_in_repo():
    with TemporaryDirectory() as tmpdir:
        # Create test Python file
        py_file = os.path.join(tmpdir, "test.py")
        with open(py_file, 'w') as f:
            f.write("""def test_function():
    return True

class TestClass:
    def method(self):
        pass
""")
        
        # Test finding Python function
        results = search_function_in_repo(tmpdir, "test_function")
        assert results['total_matches'] == 1
        assert results['matches'][0]['file_path'] == py_file
        assert "def test_function():" in results['matches'][0]['content']
        
        # Test finding non-existent function
        results = search_function_in_repo(tmpdir, "non_existent")
        assert results['total_matches'] == 0
        
        # Test with invalid directory
        with pytest.raises(ValueError):
            search_function_in_repo("/invalid/path", "test")

# Test main function
def test_main():
    with TemporaryDirectory() as tmpdir:
        # Create test file
        test_file = os.path.join(tmpdir, "test.js")
        with open(test_file, 'w') as f:
            f.write("""function testFunction() {
    console.log('test');
}""")
        
        # Test with found dependency
        model_output = "testFunction"
        result = json.loads(main(model_output, tmpdir))
        assert result['status'] == "success"
        assert len(result['dependencies_found']) == 1
        print(result)
        
        # Test with missing dependency
        model_output = "missingFunction"
        result = json.loads(main(model_output, tmpdir))
        assert result['status'] == "partial"
        assert len(result['dependencies_missing']) == 1
        
        # Test with empty input
        model_output = ""
        result = json.loads(main(model_output, tmpdir))
        assert result['status'] == "failed"

# Integration test with multiple files
def test_integration_multiple_files():
    with TemporaryDirectory() as tmpdir:
        # Create Python file
        py_file = os.path.join(tmpdir, "module.py")
        with open(py_file, 'w') as f:
            f.write("""def py_function():
    return "Python"

def helper():
    pass
""")
        
        # Create JavaScript file
        js_file = os.path.join(tmpdir, "script.js")
        with open(js_file, 'w') as f:
            f.write("""function jsFunction() {
    return "JavaScript";
}

const arrowFunc = () => {
    console.log('arrow');
}
""")
        
        # Test searching for multiple functions
        model_output = "py_function, jsFunction, arrowFunc, missing"
        result = json.loads(main(model_output, tmpdir))
        
        assert result['status'] == "partial"
        assert len(result['dependencies_searched']) == 4
        assert len(result['dependencies_missing']) == 1
        assert "missing" in result['dependencies_missing']
        print(result)

# Test ignored directories
def test_ignored_directories():
    with TemporaryDirectory() as tmpdir:
        # Create ignored directory
        os.makedirs(os.path.join(tmpdir, "node_modules"))
        ignored_file = os.path.join(tmpdir, "node_modules", "ignored.js")
        with open(ignored_file, 'w') as f:
            f.write("function shouldNotBeFound() {}")
        
        # Create valid file
        valid_file = os.path.join(tmpdir, "valid.js")
        with open(valid_file, 'w') as f:
            f.write("function validFunction() {}")
        
        # Test search
        results = search_function_in_repo(tmpdir, "shouldNotBeFound")
        assert results['total_matches'] == 0
        
        results = search_function_in_repo(tmpdir, "validFunction")
        assert results['total_matches'] == 1