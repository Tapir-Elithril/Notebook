[课程综合实践II——数据要素交易基础课程笔记](https://tapir-elithril.github.io/Notebook/sp25/data_market/note/)
课程相关内容包括：

- 数据安全
- 微观经济学/博弈论基础
- 数据估值(Shapley值的计算)
- 数据定价
- 信息定价
- 机制设计
  
## A survey of Automatic Evaluation Methods on Test,Visual and Speech Generations
“数据靶点”综述范围:在AIGC领域生成的数据中找漏洞  
**评估出价值低的数据**  
数据评估的要素：context(input),criteria,reference answer,model-generated content  
评估协议:single-wise,pair-wise,corpus-level(all generation in a test set)  
NLG(neural text generation)  
- heuristic evaluation  
  - word-overlap(词重叠)
    - 文本相似性
        BLEU,ROUGE,METEOR:n-gram overlap  
        chrF,METEOR:combine precision and recall  
        NIST,CIDEr:n-grams weight
    - 文本多样性
        Rep-n,Distinct-N:unique n-gram proportion  
        Self-BLEU:sentence-level BLEU score calculation
        EAD:adjusts(how?) the number of distinct tokens based on statistical expectation for longer texts
    - 事实一致性
        QA models + output summary与source的一致性测量
    all reference-based(HighRES is reference-free but needs annotation to serve as reference)
    可以完全reference-free吗？
  - edit-distance
    TER,WER:generated text->reference text需要改变的词数  
  - generation probability
    perplexity(PPL):对未知文本的预测准确度，PPL越低（接近1）模型预测置信度越高
    BARTScore  
    CTRLEval:designed text infilling tasks(完形填空)  
    GPTScore
  - other
    FACE:对文本交叉熵的傅里叶分析
    Mark-Evaluate:人口模型  
    Zipf:自然语言的词法规律  
    Q<sup>2</sup>:knowledge source&dialogue response  
- embedding-based evaluation:semantic similarity  
- learning-based evaluation:train on annotated(标注) data  
- LLM-based evaluation:prompt+reasoning  
- Benchmark-based evaluation  
  
## A Comprehensive Study of Shapley Value in Data Analytics
**沙普利值在数据分析流水线中的利用情况与前景**

## Data Swarms: Optimizable Generation of Synthetic Evaluation Data
**优化合成评估数据的生成推进LLM的量化评估**

## When Dynamic Data Selection Meets Data Augmentation
**动态数据选择和数据增强优化结合的训练框架**



关键点：
AIGC生成数据的漏洞：
- 数据本身：误报（幻觉），低相关性，重复性  
- 安全漏洞：敏感信息、恶意信息  
- 偏见，不公平输出
- 合规性与责任
- RCE,prompt injection,backdoor,**数据投毒**  
  
后四者属于研究的重点吗？
novelty之处：评估的方法？（具体到评估的优化方式）评估的框架？全面的评估对象（各类LLM）？
需要调研的内容：LLM数据评估的SOTA
需要的背景知识：一般的数据评估的方式
