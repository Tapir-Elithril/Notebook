# Data Target
[Paper list](paper.md)
  
## A survey of Automatic Evaluation Methods on Test,Visual and Speech Generations
“数据靶点”综述范围:在AIGC领域生成的数据中找漏洞  
**评估出价值低的数据**  
数据评估的要素：context(input),criteria,reference answer,model-generated content  
评估协议:single-wise,pair-wise,corpus-level(all generation in a test set)  
评估基本方式：heuristic,embedding-based,learning-based,LLM-based,benchmark-based 

### NLG(neural text generation)  

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
  ...  
- learning-based evaluation:train on annotated(标注) data  
- LLM-based evaluation:prompt+reasoning  
- Benchmark-based evaluation  
  
### Vision

### Audio and Speech-related

### future work
评估偏差、跨领域泛化和复杂生成系统的可扩展性

## A Comprehensive Study of Shapley Value in Data Analytics
**沙普利值在数据分析流水线中的利用情况与前景**  
沙普利值的计算：排列/组合/蒙特卡洛采样法（数据要素交易基础Lab1）
### 合作博弈模型
合作博弈在数据分析实践中的对应：  
player->数据特征/样本/数据集/派生数据  
效用->goodness-of-fit scores(accuracy)/output
应用方面：构建公平的数据要素市场；提升数据的性价比；将分析结果转化为解决实际问题
### 沙普利值应用的挑战与解决方式
#### 计算效率问题  

- 蒙特卡洛采样(MC)  
- ...  

#### 近似出错
#### 隐私保护
#### 可解释性
### SVBench

## Data Swarms: Optimizable Generation of Synthetic Evaluation Data
**优化合成评估数据的生成推进LLM的量化评估**  

## When Dynamic Data Selection Meets Data Augmentation
**动态数据选择和数据增强优化结合的训练框架**  
估计样本的局部密度与多模态语义一致性联合分布，针对性筛选适合增强的样本，同时抑制噪声或模糊数据，在保证泛化能力的前提下缩减数据集规模
### 核心技术
**data selection**  
**data augmentation**  
**combination**  
### result
在ImageNet-1k数据集上实现了训练成本降低50%且性能无损  
增强了模型的抗噪能力和鲁棒性  

## 7.4明确data target:  
不是将大部分数据低质量都视为靶点  
而是寻找质量低数据的代表性范本，上游数据对下游任务（性能）有直接损害的关键数据  
对这些数据做cluster，然后性能增强  
首要关注目标：文本/图像->**数值类型**（e.g.传感器，缺失，偏移，...）  
自动增强（后续考虑）  

尽可能在少量的条目上修改对下游task提升  
增强手法：“治疗”，update而非传统data augmentation通过增加新的样本的增强方式  
//调研传统data augmentation的方式，比较不同（可能还能结合？比如先治疗再增强）  
少量高质量的数据，大量低质量的数据  
低质量数据靶点：什么是低质量的，有哪些（类别），如何识别，如何增强  
  
调研方向：数值类型数据  
数值类型的数据集（结构化的表格类型）：质量是如何评估的（传统数据评估的算法，缺失值，错误值）；传感器/分类器：目前数据修正的方法  
传感器数据做预测/regression，kaggle上找一些数据集（天然有缺陷）  
  
下一步：调研文献，收集数据集  