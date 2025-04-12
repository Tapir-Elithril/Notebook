# vllm,sglang,lightllm,deepspeed,ollama,llama.cpp框架的异同

语言:~,python,~,~,cpp,cpp

model,gpu,scheduling policy,batching policy,kvcache policy,output policy,eviction policy  
SGLang：高性能推理引擎,提升大模型推理的吞吐量和效率，适合**企业级高并发**场景。
vLLM：高效推理与显存管理,优化显存利用率和多 GPU 并行推理，适合**服务器**端的高吞吐需求。
ollama:本地化**轻量级**部署工具,简化大模型在个人设备上的本地运行，适合快速体验和轻量级应用。


sglang部分：遗留的问题
对加载自定义模型的处理，能不能执行code
对输入的处理，有哪些保护
对传输字节流的检查，用户能多少控制网络流



vllm:kvcache same as cache(FIFO)
vllm:paged attention,continuous batching
sglang:kvcache store in radix tree(LRU) better for multi-user requests
sglang:longest prefix match(LPM) to mitigate cache thrashing(I know what you asked)
sglang的output policy?FastConstrainedDecoding:一次decode生成多个token，lookahead投机采样 `output_policy="batch"`(forward_batch_info.py)