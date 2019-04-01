## 课程重点

1. 软件体系结构的基本概念
2. 软件质量属性相关
3. 软件架构模式
4. 软件架构设计过程
5. 设计模式
6. 软件架构文档化
7. 软件架构评估
8. 软件产品线
9. 微服务架构



## Summary 中的点

#### 1. Software Architecture in General

1. What is software architecture?  （Structure, Elements, Relationships, Design ）
2. What does a software architect do? 
3. Where do architectures come from? （NFRs, ASRs, Quality Requirements; Stakeholders, Organisations, Technical Environments… ）
4. Architecture Views （Logical view, Process view, Physical view, Development view + Use case scenarios…）
5. Architectural activities and process 
6. Software architecture knowledge areas

#### 2. Quality Attributes

1. Software Requirements （Functional requirements, Quality requirements (NFRs), Constraints ）
2. Modeling quality attribute scenarios: （Source, Stimulus, Artefact, Environment, Response, Measure）
3. Availability, Interoperability, Modifiability, Performance, Security, Testability, Usability, X-ability
4. Tactics for quality attributes 
5. Architecturally Significant Requirements （How to gather and identify ASRs: Requirements, Interviews, Business goals, Utility tree）

#### 3. Architecture Patterns

1. Architecture Patterns （Context, Problem, Solution: elements + relations + constraints ）
2. Module Patterns （Layered pattern ）
3. Component-Connector Patterns （Broker pattern, Model-view-controller pattern, Pipe-and-filter pattern, Client-server pattern, Peer-to-peer pattern, Service-oriented pattern, Publish-subscribe pattern, Share-data pattern）
4. Allocation Patterns （Map-reduce pattern, Multi-tier pattern ）
5. Patterns vs. Tactics

#### 4. Designing Architecture

1. General Design Strategy （Abstraction, Decomposition, Divide & conquer, Generation and test, Iteration, Reuse ）
2. Attribute-Driven Design (ADD)  
3. Choose a part to design
   Marshal all ASRs for that part
   Create and test a design for that part
   Inputs to and outputs of ADD
   8-step process: 1. confirm requirements, 2. choose an element to decompose, 3. identify ASRs, 4.
   choose a design satisfying ASRs, 5. instantiate elements & allocate responsibilities, 6. define
   interface, 7. verify & refine requirements, 8. repeat step 2-7 until all ASRs satisfied

#### 5. Documenting Architecture

1. Views and Beyond :  Styles (viewpoints), patterns and views
   Structural views: module views, component-and-connector views, allocation views
   Quality views 
2. Documenting views: 1. build stakeholder/view table, 2. combine views, 3. prioritise & stage 
3. Beyond views: documentation info & architecture info (mapping between views) 
4. Documentation package: views + beyond

#### 6. Evaluating Architecture

1. Stakeholders involved in ATAM 
2. Inputs to and outputs of ATAM 
3. Phase 0: Partnership & preparation 
4. Phase 1: Evaluation -      1 present ATAM, 2. present business drivers, 3. present architecture, 4. identify architectural approaches, 5. generate utility tree, 6. analyse architectural approaches 
5. Phase 2: Evaluation - 2   1. present ATAM & results, 7. brainstorm & prioritize, 8. analyse architectural approaches, 9. present results 
6. Phase 3: Follow-up

#### 7. Software Product Lines

1. Software Product Lines (Engineering).

   Product = core assets + custom assets
   Reusability and Modifiability  

2. Product Line Architecture 

   Reuse: find, understand, and use (invoke)
   Variation: forms of variation * software entity varied * binding time
   Architecture: variation points

3. SPL Practice Areas and Patterns  

   29 practice areas and 22 patterns



## 最终考试

简答题、论述题、设计分析题

英⽂题⽬、中⽂或英⽂答题

个别题⽬可能需画图

基础内容70% 

⾼阶内容30%



个人认为设计分析题就是其中的高阶内容。 

画图可能还要再准备一下。



## 往年考题

### 15年考题

1. Where do software architecture come from? List five possible sources of software architecture.
2. **What distinguishes an architecture for a software product line from an architecture for a simple product?**
3. **How to model quality attribute scenarios? Graphically model two quality attributes in "stimulus-response" format: availability and performance.**
4. Describe relationships between architecture patterns and tactics. List four tactics names and describe their usage.
5. **Briefly describe the general activities involved in a software architecture process.**
6. **Mapping, and list 4 views for each style. (sa07, p.9)**
7. Explain the context, benefits and limitations of Broker Architecture Pattern.
8. Why should a software architecture be documented using different views? Give the name and purposes of 4 example views.
9. Briefly describe the fundamental principles of SOA and discuss the impact of SOA on quality attributes like interoperability, scalability and security.
10. **Describe outputs generated from each phase of ATAM process.**
11. Why SPL and MDA have high reusability? Compare and discuss their commonality and differences.

### 17年考题

1. **Briefly describe the general activities in a software architecture process, and the major inputs and outputs at each activity.** 
2. **What distinguishes an architecture for a software product line from an architecture for a single product?** 
3. What are generic design strategies applied in designing software? Give a concise working example with software architecture for each strategy. 
4. **How to model quality attribute scenarios? Graphically model two quality attributes in “stimulus-response” format: availability and modifiability.** 
5. **Describe outputs generated from each phase of ATAM process.** 
6. **Map, and list four views of each category of style.** 
7. What are ASR? List four sources and methods for extracting and identifying ASRs. 
8. Please name at least three Object-Oriented principles, and explain how they are applied in Strategy pattern? 
9. What should be included in a typical software architecture documentation package? Briefly describe each component and its purpose. 
10. Describe 4+1 view
11. 软件设计的的三个变化维度，每个维度的变化点。differing binding time如何影响可修改性和可测试性。 



Variation: forms of variation * software entity varied * binding time



### 18 年考题（梁神回忆）

1. 软件架构的关注点有哪些？利益相关方有哪些？
2. Software requirements, quality attributes, ASRs 的区别和联系
3. What is the nature of component-connector style? 以 MVC pattern 举例
4. 如何对质量属性场景建模？画出 availability 和 modifiability 的刺激-响应图
5. risks, sensitivity points, trade-off points 是什么？各举一个例子
6. **连线，并对每种 style 列出四种视图**
7. Layered pattern 和 Multi-tier pattern 的区别
8. 描述 ADD 过程
9. **为什么软件架构需要用不同的视图描述？举出四种视图的例子（列出名称和目的）**
10. 软件产品线架构如何实现可变性？描述可变性机制的工作方式
11. 设计一个飞行模拟软件，要求能模拟多种飞机的特性。为了在将来支持更多飞机种类，要求使用策略模式。画出架构图和类图
12. 太复杂，忘了





上面黑体字标出的题往年考查的概率很大，要是考的必须拿满分。

1. What distinguishes an architecture for a software product line from an architecture for a single product?



软件产品线是指具有⼀组可管理理的公共特性的软件密集性系统的合集，这些系统满足特定的 市场需求或任务需求，并且按预定义的⽅方式从⼀一个公共的核⼼心资产集开发得到。 



首先，与单个产品架构相⽐比，产品线中的产品分为custom assets 和 core assets 两部分 

所以它们的主要不同在于关注点转移:   从单独的产品到产品线的项目暗示了一个策略: 从特定的项目开发到特定业务领域产品的愿景产品线关注产品的特征，⽽单个产品架构更关注项目本身。



此外，产品线具有可重用和可变性两大特征。
产品线中的重⽤与单个产品架构中代码的重用相比，还包括了需求、业务等，几乎已经是开发者想要的了，⽽不用像单个产品架构中那样复制之后再修改。

产品线架构还拥有可变性的特点，在如单个产品架构定义正常功能之外，还定义了可改变的功能，可以识别并支持 variation points。 

总的来说，软件生产线架构与单个产品架构相比，可以减少成本、快速上市、减少风险、提高质量，更容易适应市场。



