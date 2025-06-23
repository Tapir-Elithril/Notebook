
| title | target | features | static analysis | llm | combination |contribution | notes | relevance score | year |
|:-----:|-------|-------|-------|-------|-------|-------|-------|-------|-------|
|LSAST:Enhancing Cybersecurity through LLM-supported Static Application Security Testing|reliance on a static training dataset;sensitive code exposure|the first attempt to showcase the efficiency of a locally hostable LLM-Scanner in identifying vulnerabilities|aggregating the latest vulnerability reports from **HackerOne**|encompassing both the target code and the results from the Bearer scan|Knowledge Retrieval(also in llm4vuln) Target code + Code-Abstraction-similar Vulnerability Reports + Functionality-similar Vulnerability Reports + SAST-Scanner Result|**up-to-date vulnerability insights without compromising data privacy;a combination of state-of-the-art knowledge retrieval system;a new benchmark for static vulnerability analysis**|future work:A new and improved source of vulnerabilities;algorithm for abstraction consistency;chain of thought reasoning;token limitation |10+|2024|
|IRIS: LLM-ASSISTED STATIC ANALYSIS FOR DETECTING SECURITY VULNERABILITIES | whole-repository vulnerability scan of java project | infer taint specifications and perform contextual analysis;automatically infer specifications for internal third party API;whole-repository level;systematic filtering | extract candidates and their corresponding metadata | **insert a batch of APIs in a single prompt and ask the LLM to respond with JSON formatted strings**;filtering method by contextual analysis | detect vulnerable paths by **specialized CodeQL query** for each vulnerability  |  CWE-Bench-Java dataset | / | 10 | 2024;ICLR 2025 |
|LLMSA: A Compositional Neuro-Symbolic Approach to Compilation-free and Customizable Static Analysis| reduce the dependency on compiler,customization |decomposition;parsing-based analysis |treat llm as static analyzer|Symbolic and Neural Constructor|**an analysis policy language convenient to users;lazy, incremental, and parallel prompting** mitigating the hallucinations|**Compilation-free** and Customizable,flexible problem decompose| **code slicing & prompting strategies** | 8 | 2024 |
|LATTE:Harnessing the Power of LLM to Support Binary Taint Analysis|  the first static binary taint analysis|extract dangerous flows to solve token limitation;a comprehensive prompt sequence to solve hallucinations |**Function Call Chain Extraction;Dangerous flow generation**|three prompt templates|Prompt Sequence Construction using identified dangerous flows|complete automation;improved vulnerability detection with new bug discoveries;low engineering cost| **how to ask better** | 7 |2023 |
|SecureFalcon: Are We There Yet in Automated Software Vulnerability Detection with LLMs?|bounded model checking, a form of Formal Verification (FV), can provide more accurate outcomes compared to static analyzers|only 121 million parameters derived from the Falcon-40B model and explicitly tailored for classifying software vulnerabilities||**word embeddings;decoder layers;final layer normalization**||two datasets, namely the FormAI dataset and the FalconVulnDB.|finetuning|7|2023|
|BugLens:The Hitchhiker's Guide to Program Analysis, Part II: Deep Thoughts by LLMs|reducing inherent reasoning limitations|guides an LLM to follow traditional analysis steps by assessing buggy code patterns for security impact and validating the constraints associated with static warnings|Suture and CodeQL-SOD|Structured Analysis Guidance (SAG)|||UBI in Linux kernel|7|2025|
|Llm4vuln: A unified evaluation framework for decoupling and enhancing llms' vulnerability reasoning|decouple LLMs’ vulnerability reasoning from other capabilities|up-to-date knowledge of vulnerabilities;context supplements to support the vulnerability detection process;enhanced instructions||vector database;extracted vulnerable code & calling relation for context supplement ||LLM4Vuln, a unified evaluation framework that separates and assesses LLMs’ vulnerability reasoning capabilities and examines improvements when combined with other enhancements.|vuln reasoning,knowledge retrieval| 6 |2024|
|SkipAnalyzer: A Tool for Static Code Analysis with Large Language Model|LLM-based bug detector,false-positive filter,patch generator||use Infer to detect Null Dereference and Resource Leak bugs|prompting strategy:zero-shot, one-shot, and few-shots|||prompting strategy; so simple?|5|2023|
|CleanVul: Automatic Function-Level Vulnerability Detection in Code Commits Using LLM Heuristics|dataset noise(misclassification of code commits) |heuristic approach||synthesize code changes,commit messages & context||Characterization of Code Change Categories in VFCs;VulSifter - LLM Heuristic for Identifying Vulnerability Fixes in VFCs;A Large-Scale, High-Quality Vulnerability Dataset| code commit analysis | 3 |2024|  


LSAST:
III. RELATED PAPER
A. Relevance of LLM’s in static vulnerability detection
Several papers have already demonstrated the relevance of
utilizing LLM’s for static vulnerability detection, such as ”The
Emergence of Large Language Models in Static Analysis” [21]
and ”SkipAnalyzer” [16].
B. Privacy concerns in LSAST
The paper ”Large Language Model for Vulnerability Detection” [31] emphasizes the importance of using locally hosted
LLM’s to address privacy concerns associated with third-party
LLM providers. However, the paper has not benchmarked
these locally hostable open-source LLM’s.
C. Importance of Finetuning in LSAST
Papers like ”SecureFalcon” [5] and ”Finetuning Large Language Models for Vulnerability Detection” [20] have shown
that fine-tuning LLM’s can significantly enhance their vulnerability detection capabilities. These papers also recognize that
the primary limitations of LLM’s in vulnerability detection
extend beyond just model accuracy.
D. Knowledge retrieval in LSAST
The paper ”LLM4Vuln” [23] highlights the critical role of
robust knowledge retrieval when utilizing LLM’s for vulnerability scanning. It demonstrates LLM’s capabilities in scanning
smart contract code and emphasizes that effective knowledge
retrieval is crucial for building an LLM-based SAST scanner.
However, the paper mainly explores various components of
such a scanner, with the knowledge retrieval system playing a
relatively minor role in their research.
Our paper proposes not only combining traditional SAST
scanner results with LLM’s but also enhancing the knowledge
retrieval aspect in multiple ways. We introduce new strategies
for retrieving relevant vulnerability knowledge to support the
LLM during the analysis phase.
Another paper, ”Vul-RAG” [4], implements a knowledge retrieval system using Retrieval-Augmented Generation (RAG).
While similar to our approach in using code-based similarity
search, it does not combine functionality-similarity search
or assist conservative SAST scanners, opting instead for a
standalone approach.
E. Assisting conservative SAST scanners with LLM’s
Research on assisting conservative SAST scanners with
LLM’s is sparse. ”The Hitchhiker’s Guide to Program Analysis” [11] recognizes the assistive role of LLM’s in static
analysis and presents an initial approach for achieving synergy
with LLM’s in static analysis. However, it focuses on a specific
case study of UBI bugs (Use-Before- Initialization) in Linux
kernels and does not leverage specific static analysis tools
or support a wide range of programming languages as our
approach does. In our work we evaluate LSAST on a wide
range of programming languages including javascript, php,
java and others.
Another relevant paper, ”LLM-Assisted Static Analysis for
Detecting Security Vulnerabilities” [13] leverages LLM’s to
complement traditional static analysis techniques, focusing on
using CodeQL for detailed code querying and analysis. This
approach does not directly integrate SAST scanner outputs into
the LLM prompt or implement knowledge retrieval systems as
described in LSAST, but it has the potential to be integrated
with our research in the future.