
## 目标
低质量数据靶点：什么是低质量的，有哪些（类别），如何识别，如何增强  
  
调研方向：数值类型数据  
数值类型的数据集（结构化的表格类型）：质量是如何评估的（传统数据评估的算法，缺失值，错误值）；传感器/分类器：目前数据修正的方法  
传感器数据做预测/regression，kaggle上找一些数据集（天然有缺陷）  

以下各分类中按相关性排序
## Quality Evaluation
### Scaling and assessment of data quality

### Data Quality Evaluation of Numeric Data for Classification Tasks

### A review on evaluation metrics for data classification evaluations

### The challenges of data quality and data quality assessment in the big data era

## Data cleaning(detection & repairment)
### Data Cleaning: Overview and Emerging Challenges

### Automatic Data Repair: Are We Ready to Deploy?

### Activeclean: Interactive data cleaning for statistical modeling

## Datasets
数值类型的有缺陷数据集


## Summary
数据质量评估维度  
- 完整性：缺失值比例、数据覆盖度  
- 准确性：值域检查、业务规则验证  
- 一致性：跨系统一致性、时间序列一致性  
- 时效性：数据新鲜度、更新频率  
- 唯一性：重复数据检测  
  
常见缺陷类型及修正方法  
- 缺失值处理：  
  删除法  
  均值/中位数/众数填补  
  模型预测填补(如KNN、回归)  
  多重插补法  
- 异常值处理：  
  统计方法(3σ原则、IQR)  
  基于距离的方法  
  基于密度的方法(LOF)  
  基于聚类的方法  
  基于机器学习的方法(隔离森林、One-Class SVM)  
- 不一致数据：  
  数据标准化(归一化、标准化)  
  单位统一化  
  业务规则验证与修正  
- 噪声数据：  
  平滑技术(移动平均、指数平滑)  
  分箱技术  
  回归分析  
