import requests
import json
from unresolved_dependency import *
import os

def chat_with_llm(api_key, user_message, model="gemini-2.5-pro-exp-03-25", temperature=0):
    url = "https://doi9.top/v1/chat/completions"
    
    headers = {
        "Content-Type": "application/json",
        "Authorization": api_key
    }
    
    payload = {
        "messages": [
            {
                "role": "system",
                "content": "You are a test assistant."
            },
            {
                "role": "user",
                "content": user_message
            }
        ],
        "model": model,
        "stream": False,
        "temperature": temperature
    }
    
    try:
        response = requests.post(url, headers=headers, data=json.dumps(payload))
        response.raise_for_status()  
        return response.json()
    except requests.exceptions.RequestException as e:
        print(f"请求出错: {e}")
        return None
    
def is_valid_repo_path(path):
    """检查路径是否是有效的仓库路径"""
    # 这里可以添加更具体的验证逻辑
    # 例如检查是否是git仓库：检查是否存在.git目录
    if not os.path.exists(path):
        print(f"错误：路径 '{path}' 不存在")
        return False
    
    # 检查是否是目录（而不是文件）
    if not os.path.isdir(path):
        print(f"错误：'{path}' 不是目录")
        return False
    
    # 可选：检查是否是git仓库（有.git目录）
    git_dir = os.path.join(path, '.git')
    if not os.path.exists(git_dir):
        print(f"警告：'{path}' 不像是Git仓库（缺少.git目录）")
        return False
    
    return True

def get_repo_path():
    """获取并验证仓库路径"""
    while True:
        project_path = input("请输入仓库路径: ").strip()
        
        # 处理用户可能输入的引号
        if (project_path.startswith('"') and project_path.endswith('"')) or \
           (project_path.startswith("'") and project_path.endswith("'")):
            project_path = project_path[1:-1]
        
        if is_valid_repo_path(project_path):
            return os.path.abspath(project_path)
        
        print("请重新输入有效的仓库路径\n")

if __name__ == "__main__":
    API_KEY = "Bearer sk-3AEY28Or8ORvWbwgYJo7DXftapQPk7GyMI7pDaQyi4XOpKyP"
    user_message = "Testing. Just say hi and hello world and nothing else."
    response = chat_with_llm(API_KEY, user_message)
    if response:
        assistant_reply = response['choices'][0]['message']['content']
        print(assistant_reply)
    else:
        print("Connection Error")
        exit()

    project_path = get_repo_path()
    
    while(True):
      user_message = "List the function names or the class names you did not find," \
      "if there're more than one,separate by ','." \
      "Just output the names and commas and nothing else."
    
      response = chat_with_llm(API_KEY, user_message)
    
      if response:
          if 'choices' in response and len(response['choices']) > 0:
              assistant_reply = response['choices'][0]['message']['content']
              print(assistant_reply)
              dependencies = extract_dependencies(assistant_reply)
              results = search_function_in_repo(project_path,dependencies)
              response = chat_with_llm(API_KEY, results)
              assistant_reply = response['choices'][0]['message']['content']
              print(assistant_reply)
