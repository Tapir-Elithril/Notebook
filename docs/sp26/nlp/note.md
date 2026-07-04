# 自然语言处理导论
ftp://dl4nlp2026:nlp2026@10.214.112.254
主机: 10.214.112.254  
用户: dl4nlp2026  
密码: nlp2026  
端口: 留空  
## Lecture 1:Introduction
## Lecture 2:Deep Learning Basics
machine learning:f(input) = output,f is the learnt model  
1. define a set of function and train the models using training data  
2. evaluate the goodness of function f  
3. pick the best function f*  

Neural Network:omitted  
shallow and wide vs. deep and narrow:same number of parameters but deep means more pieces(piecewise linear,the addition of more linear functions)  
training data:loss minimization  
best function selection:gradient descent  
pick the initial value of w  
compute $\partial L/\partial w$  
move $-\eta\partial L/\partial w$,$\eta$ can be defined using weight decay/adam(adaptive momentum)  
problem of adam:memory of second-derivative  
Muon(24.12):low-rank,sparse matrix $M\approx N=OO^\top= U^\top IV$  
local minima,saddle point(鞍点),plateau  
## Lecture 3:Word Embedding
Manifold assumption语义流形：通过一个空间，在这个空间移动可以进行语义的比较  
represent the meaning of a word:  
- discrete representation/one-hot([0,0,...,0,1,0,...,0])  
  no natural notion of similarity  
- Distributional similarity based representations/word2vec  
  continuous bag-of-word (CBOW):eat an __ every day -> apple  
  skip-gram (SG):apple -> eat an every day  
  输入词->预测上下文->计算与窗口上下文词的误差（熵）->反向传播  
  hierarchical softmax:huffman encoding  
  negative sampling:对不在上下文的词给低分（对比学习）  

Application:  
- Word similarity  
- Machine translation  
- Part-of-Speech and Named Entity Recognition
- Relation Extraction
- Sentiment Analysis
- Co-reference Resolution
- Clustering
- Semantic Analysis of Documents  

Limitations:  
- ambiguity  
- debuggability(颜色区分困难)  
- sequence(顺序)  

## Lecture 4:RNN
RNN  
![](image.png)  
Deep-RNN  
![](image-1.png)  
Bidirectional-RNN  
![](image-2.png)  
Naive RNN and LSTM  
![](image-3.png)  
where $c$ changes slowly and $h$ changes faster  
input gate:$z^i=\sigma(w^ix^th^{t-1})$  
forget gate:$z^f=\sigma(w^fx^th^{t-1})$  
output gate:$z^o=\sigma(w^ox^th^{t-1})$  
$z=tanh(wx^th^{t-1})$  
$c^t=z^f\otimes c^{t-1}+z^i\otimes z$  
$h^t=z^o\otimes tanh(c^t)$  
$y^t=\sigma(W'h^t)$  
GRU:$h^t=z\otimes h^{t-1}+(1-z)\otimes h'$  
stacked LSTM,nested LSTM  
### RNN for NLP
representing a sentence:classification,conditioned generation,retrieval  
representing a context within a sentence(read context up until that point):tagging,language modeling,calculating representations for parsing  
Encoder-decoder model for translation  
### Attention
sentence-vector encoding  
decoding:linear combination of vectors using attention weights  
calculate weight for each query-key pair,then softmax  
combine together value vectors by taking the weighted sum  
attention score function:scaled dot product  
$$
a(q,k)=\frac{q^Tk}{\sqrt{|k|}}
$$
### pointer network
looking for a convex hull(find a few points to wrap all the points)  
Seq2seq model:output size of decoder is fixed, not suitable for dynamic results  
attention mechanism  
encoder:city coordinates  
decoder:attention scores as probability and choose the highest point  
## Lecture 5:Natural Language Generation and Neural Machine Translation
### NLG
[Definition] any text generation,including translation,summarization,dialogue,creative writing,question answering,image captioning,...  
Language modeling(next token prediction):$P(y_t|y_1,...,y_{t-1})$ called:RNN-LM  
Conditional LM(with input x):$P(y_t|y_1,...,y_{t-1}|x)$,encoder-decoder  
![](image-4.png)  
faster generation dLLM:从噪声矩阵开始，每步同时预测所有位置（依据置信度评估的渐进式解码）  
training process(Teacher Forcing):每次token prediction都由一个“teacher”给出正确答案  
schedule sampling:逐渐增加用自己输出token进行prediction的概率，提高抗风险能力  
#### decoding algorithm
##### argmax(greedy)/sampling
sentence generation:argmax/sampling(still sometimes same answer due to KV-cache)  
pure sampling:greedy decoding,top-n sampling:samples restricted in top-n most probable words  
##### beam search
beam search decoding:On each step of decoder, keep track of **the k most probable partial sequences** (which we call hypotheses)
e.g. Given a generated sequence:`I am` with next token probability:`a=0.4,very=0.3,not=0.2,the=0.1`,K=2  
preserve the top-K=2 sequence:`I am a`,`I am very` with next token probability:  
`I am a`:`student=0.5,teacher=0.3,person=0.2`,`I am very`:`happy=0.6,excited=0.3,sad=0.1`  
Then the probabiity of sequence:`I am a student=0.20,I am a teacher=0.12,I am a person=0.08,I am very happy=0.18,I am very excited=0.09,I am very sad=0.03`,then preserve the top-K=2 sequence:`I am a student=0.20,I am very happy=0.18`,repeat.  
beam size K:  
- small:similar to greedy  
- large:$P(sentence)=P(w1) × P(w2) × ... × P(wn)$ means the model will prefer short answers;boring and general answer(`I don't know`) because general words have slightly larger probability  
##### temperature
softmax:$P_t(w)=\frac{\exp(s_w)}{\sum_{w'\in V}\exp(s_{w'})}$  
temperature parameter $\tau$:$P_t(w)=\frac{\exp(s_w)/\tau}{\sum_{w'\in V}\exp(s_{w'}/\tau)}$  
higher temperature means more **creative** answers,because it smooths the probability of next token  
```python
z=[2.0, 1.0, 0.5]
T=0.5
z/T = [4.0, 2.0, 1.0]
exp(z/T) = [54.6, 7.4, 2.7]
概率 = [0.84, 0.11, 0.05]  # 高度集中在最高分
T=1.0
z/T = [2.0, 1.0, 0.5]
exp(z/T) = [7.4, 2.7, 1.6]
概率 = [0.63, 0.23, 0.14]  # 保持原始分布
T=2.0
z/T = [1.0, 0.5, 0.25]
exp(z/T) = [2.7, 1.6, 1.3]
概率 = [0.48, 0.29, 0.23]  # 分布更均匀
```  
Ensembling:combine the predictions from multiple models  
#### evaluation
human evaluation  
BLEU:how many n words in sequence(n-gram) matches the reference  
e.g. `Reference=Taro visited Hanako`,`System=The Taro visited the Hanako`,1-gram=3/5,2-gram=1/4  
brevity(too short generation penalty)=min(1,|System|/|Reference|)=1  
$BLEU_2=(3/5*1/4)^{1/2}*1=0.387$  
bad for comparing very different systems  
METEOR:consider recall(for lacking information),hierarchical matching:precise matching,stem(词干) matching,synonym(同义词) matching,order penalty  
Perplexity困惑度:how many candidate words are there for each prediction in average  
```python
文本: "The cat is sleeping"
模型预测概率:
- P("The" | start) = 1.0
- P("cat" | "The") = 1.0
- P("is" | "The cat") = 1.0
- P("sleeping" | "The cat is") = 1.0

计算:
几何平均 = (1.0 × 1.0 × 1.0 × 1.0)^(1/4) = 1.0
Perplexity = 1/1.0 = 1.0 ✅

文本: "The cat is sleeping"
模型预测概率:
- P("The") = 0.8
- P("cat" | "The") = 0.6
- P("is" | "The cat") = 0.7
- P("sleeping" | "The cat is") = 0.5

计算:
几何平均 = (0.8 × 0.6 × 0.7 × 0.5)^(1/4)
         = (0.168)^(1/4)
         ≈ 0.639
Perplexity = 1/0.639 ≈ 1.56
# 模型平均在 1.56 个词之间犹豫
```
### Neural Machine Translation
RBMT(rule-based),EBMT(example-based),SMT(statistical),NMT(neural)  
SMT:$argmax_yP(y|x)\propto argmax_xP(x|y)P(y)$  
$P(x|y)\rightarrow P(x,a|y)$,假设存在已知分布的隐变量$a$，通过概率估算隐变量的结果  
对齐alignment:人工标注单词翻译间的对应关系，can be one-to-many,many-to-one,many-to-many  
NMT:(bidirectional) encoder-decoder framework  
seq2seq model:very long training,translation breaks down for long sentences  
V1:encoder-decoder  
V2:Attention based encoder-decoder  
V3:Bi-directional encoder layer  
V4:multi-layer/deep encoder and decoders  
![](image-5.png)  
V5:parallelization  
V6:residuals to solve vanishing gradients  
translation quality:human evaluation from score 0-6  
[problem] not scale  
[solution] multilingual model:prepend source with additional token to indicate target language,e.g.<2en>,to english  
zero-shot translation:given English-Korean,English-Japanese translation,Korean-Japanese translation can be achieved zero-shot  
code-switch:语言混杂 is allowed  
## Lecture 6:Transformers(1)
### self-attention  
input:$x^i$,word vector:$a^i=Wx^i$,$q,k,v=W^{q/k/v}a^i$  
scaled dot product attention:$\alpha_{1,i}=q^1\cdot k^i/\sqrt{d}$  
$\alpha_{1,1},\alpha_{1,2},\alpha_{1,3},\alpha_{1,4}\rightarrow softmax\rightarrow\hat{\alpha}_{1,1},\hat{\alpha}_{1,2},\hat{\alpha}_{1,3},\hat{\alpha}_{1,4}$  
$b^1=\sum_i\hat{\alpha_{1,i}}v^i$  
$b^1,b^2,b^3,b^4$ can be computed in parallel  
all matrix multiplication,accelerated by GPU  
### multi-head self-attention
different head(query vector) focuses on different aspects  
![](image-6.png)  
elf-attention的计算是对称且无序的，无法感受到词语在序列中的先后顺序,需要positional encoding显式注入位置信息  
positional encoding:a unique positional vector(each $x^i$ appends a one-hot vector $p^i$)  
Sinusoidal位置编码  
RoPE旋转位置编码:通过旋转矩阵来编码单词在序列中的绝对位置，同时让注意力机制自然地感知到相对位置  
计算注意力时，两个向量之间的角度差（即旋转后的方向差异）自然地表达了它们在序列中的距离远近  
### Transformer
![](image-7.png)  
Add & Norm:Residual link:$a + b$;layer normalization  
layer normalization:单样本归一化（包括均值，方差，可学习的缩放和平移参数）  
feed forward:very large MLP  
MoE混合专家：复制多份FFN（多个专家），每个token只去几个专家，批量token路由发送数据    
## Lecture 7:Transformers(2)
### MLP Mixer
for images  
$channels * patches\stackrel{T}{\rightarrow} patches * channels\rightarrow MLP_1\stackrel{T}{\rightarrow}channels * patches\rightarrow MLP_2\rightarrow Mixer$  
greatly reduce time complexity(transformer:$O(N^2)$)  
not gain popularity because of kv-cache  
### Mamba
a challenger of Transformer  
recall RNN:$H_t=f_{A,t}(H_{t-1})+f_{B,t}(x_t),y_t=f_{C,t}(H_t)$  
并行训练：ignore forget gate:$f_{A,t}\rightarrow$ linear attention:$H_t=H_{t-1}+v_tk_t^T,y_t=H_tq_t$  
linear attention is RNN without forget gate $f_{A,t}$
linear attention is self-attention without softmax  
retention network(RetNet):$H_t=\gamma H_{t-1}+v_tk_t^T,y_t=H_tq_t$  
gated retention:$H_t=\gamma_t H_{t-1}+v_tk_t^T,y_t=H_tq_t,\gamma_t=sigmoid(W_{\gamma}x_t)$  
more variants:$H_t=G_t\otimes H_{t-1}+v_tk_t^T,G_t=e_ts_t^T$  
Mamba:linear attention with variants  
### pretrain model
tokenized vector embedding:Word2Vec,FastText(char),CNN  
contextualized world embedding:LSTM,self-attention layers,tree-based model  
smaller model  
- network pruning  
- knowledge distillation(teacher&student)  
- parameter quantization  
- architecture design(transformer-XL:segment-level recurrence with state reuse)  
### fine-tune
pretrained model + task-specific layer  
input:one sentence,multiple sentences(using special token:[SEP])  
output  
- one class:special token [CLS]  
- class for each token:classifier for each token  
- copy from input(extraction based Q&A)  
- general sequence:pretrained model as encoder,task specific as decoder?$\rightarrow$encoder as decoder(input sequence + [SEP] + output sequence),but the model sees the input and output(answer) together

[Solution] 因果注意力(causal attention):掩码矩阵使llm只能看见先前的位置  

## Lecture 8:How to train your LLM
#### Adaptor
small network after feed-forward for PERT  
often a bottleneck forward network:先降维，激活，再升维  
LoRA(Low-Rank Adaptor):a layer mount beside the main network(flexible)
weighted features 
feedforward:layer 1 -> x1 -> layer 2 -> x2 -> w1x1+w2x2 -> task specific(w1,w2 is learnt in downstream tasks)  
### How to pretrain
self-supervised learning:given a sequence/image/...,predict some part of it based on the other parts  
masking input,encoder as decoder,causal attention,bidirectional next token prediction  
### LLM implementation
1. forward & backward:input -> weights -> loss -> backpropogation -> gradient -> weights  
2. memory:for 8B model,weights=32GB,adamW momentum=32GB,variance=32GB,fp16 computation on GPU:weights=16GB,gradients=16GB,total=128GB  
3. activation:16k tokens context -> 32 layers * (attention=40GB + feed forward=2.2GB)=1.35TB  
4. batch size:generally 4-60M tokens per batch(DeepSeek V3:batch size=1920 for 32K context,61M tokens)  
global batch size = mini batch size * gradient accumulation  
#### parameters,gradients and optimizer states
DeepSpeed-Zero Redundancy Optimizer (ZeRO):  
Zero-1:optimizer separation(leveraging bandwidth for transmitting,NVLink)  
Zero-2:gradient separation  
Zero-3:model parameters separation(commonly used,not recommended)  
Zero-Offload:GPU->CPU communication，very slow  
#### activations
1. kernel:PyTorch -> torch.compile() -> Triton -> CUDA  
2. flash attention:$O(N^2)\rightarrow O(N)$  
store Q,K,V in CPU,computing by transmitting blocks to GPU  
3. Liger kernel(optimized Triton code)  
`AutoLigerKernelForCausalLM`  
#### quantization
1. lossy compression:32 bit精度->8/4/2/1bit  
## Lecture 9:Model compression and Data-efficient fine-tuning
### quantization
post-training:floating point numbers  
int8 quantization:[0.5,20,-0.0001,-0.01,-0.1]  
max = 20  
round(127/20 * [0.5,20,-0.0001,-0.01,-0.1])=[3,127,0,0,-1]  
model-aware quantization:  
GOBO:BERT weights in each layer fit a Gaussian distribution -> quantize 99.9% of parameters and remain the 0.1%  
LLM.int8:8-bit vector-wise quantization for 95% normal parameters + 16-bit decomposition for outliers  
#### quantization-aware training
binarized neural network:weights are -1 and 1 everywhere  
Layer-by-Layer Quantization-Aware Distillation:ZeroQuant  
memory compression:Q-LORA  
### pruning
set a number of parameters to zero  
Lottery ticket hypothesis:training pruned(delete unnecessary parameters) randomly-initialized network can be better than training full randomly-initialized network  
Wanda:pruning matrix $W$ based on $S=|W|\cdot \|X\|_2$  
$W=\begin{bmatrix}4&0&1&-1\\3&-2&-1&-3\\-3&1&0&2\end{bmatrix},\|X\|_2=\begin{bmatrix}1&2&8&3\end{bmatrix},S=\begin{bmatrix}4&0&8&3\\3&4&8&9\\3&2&0&6\end{bmatrix}\rightarrow W'=\begin{bmatrix}4&0&1&0\\0&0&-1&-3\\3&0&0&2\end{bmatrix}$
problem of unstructured pruning:limited sparse data structure supporting hardware  
structured pruning:remove entire components  
coarse-to-fine structured pruning:learn masks that control which components to turn off  
coarse pruning:entire self-attention or feed-forward components  
fine pruning:attention heads and hidden state dimensions  
### distillation
all parameters are changed student model  
training data are generated by teacher model  
weak supervision:labels from other places,e.g.remote supervision:label from the third-party  
hard target:one-hot label  
soft target:probability distribution  
born-again NN:teacher -> student 1 -> student 2 -> student k  
ensemble student 1 to k:better than teacher  
word-level distillation:match the distribution of words at each step with the teacher distribution
sequence-level distillation:maximize the probability of the output generated by the teacher  
DistilBERT:initialize with BERT weights;soft target imitation;mask language pretrain task;consine similarity of hidden layer vectors
Self-Instruct:automatic instruction tuning dataset generation  
Prompt2Model:prompt -> retrieve data,generate data,retrieve pretrained model -> deployment-read model
## Lecture 10:Data-efficient fine-tuning and RL
Adapter:inside Transformer, after Feed-forward, only adapters are updated  
LoRA:Low-Rank Adaptation beside Feed-forward  
```python
# 标准微调 vs LoRA

# 标准微调（更新所有权重）
output = W·x

# LoRA（只更新低秩矩阵）
output = W·x + ΔW·x = W·x + (B·A)·x
# W冻结不更新
# 只训练A和B
其中: B ∈ ℝ^(d×r), A ∈ ℝ^(r×k), r << min(d,k)
```
prefix/prompt tuning:see homework3  
early exit:add a confidence predictor for each classifier after each Transformer layer, early output for enough confidence  
semi-supervised learning:few-shot(some labeled training data and a  large amount of unlabeled data)  
Promptless fine-tuning：直接在预训练模型上添加分类头并微调所有参数，不使用任何提示模板。使预训练模型适应不同的下游任务，如BERT  
Fixed-prompt tuning：使用固定的自然语言提示模板，但微调整个模型的所有参数以适应任务。  
Prompt+LM fine-tuning：使用可学习的软提示向量，同时微调提示和整个语言模型的所有参数。  
Tuning-free prompting：完全不进行任何训练，直接使用精心设计的提示模板引导冻结的预训练模型进行零样本推理，即硬提示学习  
Fixed-LM prompt tuning：冻结整个语言模型的所有参数，只训练可学习的连续提示向量（软提示），即软提示学习  
![](image-8.png)  
样本多 → 可训练参数可以多 → 充分微调  
promptless fine-tuning,fixed-prompt tuning,prompt+LM fine-tuning可训练参数100%，模型参数多不会导致过拟合，可以充分利用数据学习的细粒度特征 
样本少 → 可训练参数必须少 → 防止过拟合  
tuning-free prompting训练参数0%，fixed-LM prompt tuning可训练参数<1%,利用模型的先验知识，极大降低过拟合风险  
### RL
see Machine Learning in fa25 
Q-learning:action based  
policy based:for continuous values   
## Lecture 11 & 12:GPTs：ChatGPT, GPT-4, and etc
BERT:填词，预训练用于各类nlp任务  
GPT:选词接龙，语境学习用于语言生成（无需训练）  
语境学习(in context learning):few-shot(example) learning,one-shot learning,zero-shot learning  
scaling laws and emergent ability  
### 大模型训练与对齐
pretraining,post-training/alignment(SFT,RLHF持续学习/终身学习)  
#### pretrain
以盘古为例  
语料->算法->框架->评测  
垃圾文本过滤：人工精细化评估+盘古α小模型快速批量验证，大规模降低文本数据量  
大集群训练：内存墙、性能墙、效率墙、调优墙  
解决方法：scale out并行、scale up内存优化  
大集群训练快速故障恢复：CKPT保存、故障检测隔离、资源重调度、加载CKPT、恢复  
#### supervised fine-tuning(SFT)
Pretrain style:人工智->能  
SFT style:input:USER:你是谁？output:我是->...(遵循结构化回答数据)  
Non-instructional fine-tuning:直接用输入-输出对进行任务微调  
less is more for alignment,quality is all you need(RuoZhiba)  
ChatGPT:GPT3.5->指令微调->人类反馈->RL  
#### 人类反馈的强化学习（RLHF）
RL style:Q:杭州最高山是哪座?A:不知道(bad)/如意尖(good)  
Proximal Policy Optimization(PPO)  
policy gradient:trajectory $\tau = \left\{s_1,a_1,s_2,...,s_T,a_T\right\}$  
$p_{\theta}(\tau)=p(s_1)p_{\theta}(a_1|s_1)p(s_2|s_1,a_1)p_{\theta}(a_2|s_2)p(s_3|s_2,a_2)...$  
$R_{\theta}=\sum_{\tau}R(\tau)p_{\theta}(\tau)=\mathbb{E}[R(\tau)]$  
$\nabla R_{\theta}=\sum_{\tau}R(\tau)\nabla p_{\theta}(\tau)=\sum_{\tau}R(\tau)p_{\theta}(\tau)\nabla\log p_{\theta}(\tau)$  
problem:policy gradient is based on random sampling,so it leads to **data inefficiency and unstable update**    
solution(PPO):make effective use of limited data  
1. mini-batch training(on-policy -> off-policy/observing) using importance sampling   
e.g. sample from Gaussian distribution using uniform sampling(25% accept < -0.5,25% accept >0.5,50% accept between -0.5 and 0.5)  
无偏high variance  
2. regularization KL  
3. clip objective
### Catastrophic Forgetting
catastrophic forgetting because of parameters changed by SFT(not only deliberate attack)  
result:security loss,general knowledge forgets  
large models doesn't perform better in forgetting prevention  
LoRA learns less forgets less  
tradeoff:professional competence increases,general ability losses  
[Solution] experience replay/memory bank:reserve some training data while fine-tuning  
[Problem] training data is not open-source  
[Solution] distillation from the LLM  
pseudo experience replay(paraphrase):input data from the Internet -> ask the model to paraphrase -> add them into the fine-tuning data  
## Lecture 13:reasoning model 
### Deepseek
GPT-o1 for training  
V3:非推理模型提示工程：角色，功能，技能，约束，工作流程，输出格式，示例  
推理模式：模型自制提示词<think> 
#### 架构设计
DeepSeekMoE:(Mistral:8 experts,Grok:20)671B model with 58 MoE layer,each layer(except the first three) consists of 1 shared expert and 256 router experts.  
Each layer activate 1 shared expert and 8 router experts -> 37B  
H800硬件稍弱，冗余专家可以避免异常  
Why MoE?  
Large model needs to be separated into many devices -> high requirement for communication -> NVIDIA NV-link 900G/s but has a limit of 1000 GPUs -> more GPUs need pod集群 network -> high cable communication latency   
[Solution] SYNC system at NV-link -> system connect by cables -> MoE for ASYNC pods -> faster and easier development  
Multi-Head Latent Attention(MLA):降维QKV存储到cache  
Multi-Token Prediction(MTP)  
#### 量化训练
FP8  
混合精度细粒度量化:激活->1* 128 tile条形分组，权重->128* 128 block分块  
乘法量化FP8,加法高精度FP32  
FP4 for scaling factor(指数范围)  
#### 并行计算
16路流水线+64路专家并行，ZeRO-1  
DualPipe双向流水线,reduce bubble;warp specialization计算与通信重叠;内存优化重计算    
### 推理模型
o1-preview:quiet thought(latent space非自然语言token),inference-time scaling  
question -> <think> verification/explore/planning </think> -> answer  
Test-time compute(in AlphaGo):MCTS  
Test-time scaling:scaling scaling law:longer test-time compute(reasoning) can complement train-time compute,achieving similar performance  
#### CoT
short CoT:few-shot CoT(examples),zero-shot CoT('Let's think step by step')  
long CoT  
#### 模型推理工作
input -> 'give me the first step' -> output many first steps -> 'this first step is good,now give me the second step' -> ...  
[problem] how do we know which step is good?  
Long CoT can be only **guided out** in some strong LLMs  
[solution] large language monkeys:足够多尝试，模型可以得到正确答案  
Majority voting:同一个问题多问几次，选出最多答案/最高confidence的答案  
Best-of-N:verifier(another LLM) gives a score for each output  
#### knowledge distillation
feed the reasoning process of a reasoning model to a base model  
#### RL
DeepSeek-v3-base use RL(neglect reasoning process,only focus on answer) with accuracy as reward -> DeepSeek-R1-Zero  
Aha Moment  
R1-Zero only for math and coding  
use R1-Zero + data synthesis数据合成,human annotation,few-shot prompting,direct prompting for reflection and verification -> imitation learning   
v3-base use imitation learning -> model A,then RL with reward of accuracy and language consistency -> model B,then v3 as verifier(GRPO,Group Relative Policy Optimization)      
v3-base use imitation learning of the result of model B + verifier -> model C,then RL with reward of safety and helpfulness -> DeepSeek-R1  
### 多路径推理
[problem] overthinking for easy question,give up for very difficult problem  
[solution] 模型选择；输出长度限制；多路径推理与结果聚合，利用硬件并行计算  
adaptive parallel reasoning:自适应并行推理  
parallel method:sample K answers and score independently,then select the highest score one  
sequential method:LLM is trained to extend reasoning path until reaching correct answer  
sample set aggregator样本集聚合器:hybrid of parallel and sequential method  
### 质疑
推理相比提示词工程是否有用  
RL收益大小  
悖论性行为（复杂问题时放弃）  
干扰信息("Interesting fact:cats sleep for most of their lives")  
对抗性触发：overthinking  
轻微分布导致模型下降（改变数字）  
CoT限制会导致不连贯步骤  
强制模型以用户语言思考导致准确率降低  
## Lecture 14 & 15:LLM development trend
### 专业模型与检索增强
gigantic LLM training set for pretraining,specific knowledge base for fine-tuning -> fine-tuned LLM  
smart retriever look-up specific knowledge base by index embedding(kv vector database)  
question + relevant documents as asking input  
#### context window
the needle in the haystack test:大海捞针  
通用模型 + 无限上下文 ≠ 专业模型  
context rot上下文腐烂：中间信息缺失  
### context engineering 
context:instructions/system prompt,long-term memory,state/history(short-term memory),user prompt,retrieved information(RAG),avaliable tools,structured output  
[problem] system prompt与tool output输出量不协调，导致关键信息遗忘  
context engineering:  
- write context  
  - long-term memories(across agent session) -> cloud  
  - within agent session -> scratchpad  
  - state(within agent session) -> file system/database  
- select context  
  - retrieve relevant tools  
  - retrieve from scratchpad  
  - retrieve long-term memory  
  - retrieve relevant knowledge  
- compress context  
  - summarize context to retain relevant tokens  
  - trim(删除) context to remove irrelevant tokens  
- isolate context  
  - partition context in state  
  - hold in environment/sandbox  
  - partition across multi-agent  

### 模型
开源与闭源  
领域模型与垂直模型  
### 算力
- Blackwell Ultra架构  
- Rubin平台  
- 边缘计算设备  

专用芯片  
TPU v7——ironwood  
存算一体芯片  
### 数据
多模态：教育，图表理解与数据推理，内容生成，调研  
联觉：可控知识注入机制，图像->文本instruction-specific visual-prompt  
Momentor:视频大模型，细粒度时间理解  
语音合成大模型：NaturalSpeech3，因子化扩散模型实现零样本语音合成  
GPT-4o:realtime conversational speech  
New Tokenizer:Auto-Encoding Morph-Tokens  
视觉理解：丢弃部分特征进行视觉抽象  
视觉生成：尽可能保留视觉细节  
图像-文本对统一自回归训练，文本自回归图像重建，基于指令微调的文本自回归  
增量式模态扩展  
HealthGPT  
混元视频（Sora）  
视频生成LanDiff  
Sora2  
Seedance 2.0  
### 算法
GPT-4:调用工具，角色扮演，agents  
多样化agent研究:tools,planning,memory,MAS,evaluation,coding agent,research agent,generalist agent    
multi-model agent:HuggingGPT  
AutoGPT  
通用虚拟智能体（浏览器）  
推荐系统  
openclaw:context engineering  
### 应用
通用机器人  
Helix  
世界模型:对物理世界的因果理解，关于环境如何运作的抽象表征,感知，预测，推理    
### 思考
认知与感知，未来与担忧  

