# LLM Infra
SGLang vllm 
ollama llama.cpp
- 相应论文
- 代码功能
- 部署模型
- API分类与功能
  
论文：
[kvcrush]https://arxiv.org/pdf/2503.00022
Time Will Tell: Timing Side Channels via Output Token Count in Large Language Models
Are Your LLM-based Text-to-SQL Models Secure? Exploring SQL Injection via Backdoor Attacks
A Practical Memory Injection Attack against LLM Agents
https://zhuanlan.zhihu.com/p/24361825625


RAG(retrieval-augmented generation)外部知识库检索
embedding模型解析

ollama:
代码未开源 基于llama.cpp

未授权访问
数据泄露
框架历史漏洞攻击
API滥用

鉴权 
进程隔离（TEE Trusted execution environment）
联网 OLLAMA_HOST = 0.0.0.0

gpt-4o vLLM
deepseek-r1/v3/v2
llama2/3
qwen,gemma,llava

API

- Generate
- Embedding:获取嵌入向量
- Completion:自动补全
- Chat:多轮对话
- Fine-tuning:微调
- Model management:管理模型
- Health check:服务状态
- Tokenization:文本分词
- Batch processing:批量处理
- Custom
- 推理
- 评估

llama.cpp:
代码功能：llama_model,CPU/GPU buffer type,buft,create_tensor,weight_alloc,kv_cache,scheduler,graph,memory_alloc

通过AI infra向LLM知识库投毒
同一网络同一进程下模型信息窃取 哪些资源是共享的
llama.cpp.源码剖析