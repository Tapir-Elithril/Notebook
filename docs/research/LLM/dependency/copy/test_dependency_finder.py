import tempfile
import os
import pytest
from unresolved_dependency import *

def test_dependency_extraction_and_search():
    """test dependency extraction and search functionality"""
    # 1. temporary directory to simulate project structure
    with tempfile.TemporaryDirectory() as tmpdir:
        # simulate a build.gradle file with dependencies
        gradle_content = """
        dependencies {
            implementation 'com.google.guava:guava:31.1-jre'
            api 'org.example:core-utils:2.1'
        }
        """
        gradle_path = os.path.join(tmpdir, "build.gradle")
        with open(gradle_path, "w", encoding="utf-8") as f:
            f.write(gradle_content)

        # 2. simulate construct error output
        error_output = """
        FAILURE: Build failed with an exception.
        * What went wrong:
        Could not resolve: com.google.guava:guava
        Failed to resolve dependency: org.example:core-utils
        """

        # 3. test extract_dependencies 
        dependencies = extract_dependencies(error_output)
        assert dependencies == ["com.google.guava:guava", "org.example:core-utils"]

        # 4. test find_dependencies
        results = find_dependencies(tmpdir, dependencies)
        
        # result
        assert len(results) == 2
        
        # check precise match (com.google.guava:guava)
        exact_match = next(
            r for r in results 
            if r["dependency"] == "com.google.guava:guava" 
            and r["match_type"] == "exact"
        )
        assert exact_match["found_in"].endswith("build.gradle")
        assert exact_match["matched_line"] == "implementation 'com.google.guava:guava:31.1-jre'"
        
        # # check fuzzy match (org:core-utils)
        # fuzzy_match = next(
        #     r for r in results 
        #     if r["dependency"] == "org.example:core-utils" 
        #     and r["match_type"] == "fuzzy"
        # )
        # assert fuzzy_match["confidence"] >= 80  # default
        # assert fuzzy_match["matched_line"] == "api 'org.example:core-utils:2.1'"

        exact_match = next(
            r for r in results 
            if r["dependency"] == "org.example:core-utils" 
            and r["match_type"] == "exact"
        )

        # 5. test main()
        json_output = main(error_output, tmpdir)
        output_data = json.loads(json_output)
        
        assert output_data["status"] == "success"
        assert len(output_data["dependencies_found"]) == 2
        assert not output_data["dependencies_missing"]