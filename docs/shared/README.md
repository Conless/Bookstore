# 书店管理系统

SJTU ACM 班 2022 级程序设计课程大作业

## 目录

* [简介](#简介)
* [作业说明](#作业说明)
  * [评测方式](#评测方式)
  * [块状链表库](#块状链表库)
  * [分数组成](#分数组成)
  * [时间表](#时间表)
* [项目说明](#项目说明)
  * [开发要求](#开发要求)
    * [开发文档](#开发文档)
    * [Git 版本管理](#git-版本管理)
    * [代码风格](#代码风格)
  * [业务需求](#业务需求)
  * [Bonus](#bonus)
  * [扣分](#扣分)

## 简介

实现一个用 C++ 语言编写的书店管理系统，用于向店家和顾客提供图书检索与购买相关服务。

本项目目标如下：

- 培养学生工程开发的能力（开发文档的编写与程序的封装等）；
- 培养学生的代码管理能力（git 的使用），拥有良好的代码规范意识；
- 提升学生的编程学习与实践能力（块状链表的学习实现）；
- 培养学生对编写软件的兴趣（见 [bonus](#bonus)）。

### 关于本仓库

<!-- - 本仓库中主要文件为助教提供的块状链表链接库，具体使用方式见仓库中 `lib`, `include` 及 `src` 文件夹中内容；-->
关于本仓库有任何问题欢迎联系助教，也可以直接 pull request；本仓库内容将维护至本作业结束，请保持关注题面更改，助教也会及时发布相关通知。

## 作业说明

### 评测方式

公开的评测数据可以从 [SJTU jBox](https://jbox.sjtu.edu.cn/l/b1x5MN) 下载。

注意，每个 testcase 为最小评测数据单元；在测试同一 testcase 的多个输入（.in）过程中，对于每个输入，都会运行学生程序，完成后关闭程序，再以下一个输入运行学生程序，但过程中不会清除学生程序运行生成的数据文件。而每个 testcase 测试结束后会清除所有学生程序生成的文件，再运行下一个 testcase。

Online Judge（以下简称 OJ）提交方式为提交 git repo 链接，提交内容应为形如 `https://github.com/username/repo` 的链接。编译评测方式详见 OJ 首页说明。OJ 使用沙盒评测文件读写。编译生成的可执行文件名应为 `code`，否则 OJ 无法运行。
    
由于网络原因可能会导致评测机 clone 仓库失败。

<!-- 仓库内容过大（如将解压后的数据文件或 build 内容一并放入仓库）导致的问题后果自负。（Tip：可以使用 Github 仓库加速通道链接提交作业，例如 Chrome 插件 [GitHub 加速](https://chrome.google.com/webstore/detail/github%E5%8A%A0%E9%80%9F/mfnkflidjnladnkldfonnaicljppahpg)）-->

本地评测可用脚本评测，评测脚本已包含于数据包中，在含有 `./code` 的目录下运行脚本即可。例如你的 `code` 在 `./cmake-build-debug`，数据在 `./data`，则运行 `cd cmake-build-debug; ../data/judge` 即可。如运行评测脚本出现问题，请联系助教。

评测数据量（帐户和图书数量）不会超过 $1\times10^5$ 数量级。

### 块状链表库

助教提供一个备用的块状链表库，见 [libull 仓库](https://github.com/ACMClassCourse-2022/libull)。正常情况下你不应该使用这个库，但是如果你的文件存储实在调不出来，也可以暂时用这个库先写主体逻辑。

### 分数组成

本作业满分为 100%，最终将以本作业占本课程成绩总分分数折算入课程成绩。

**注意：若使用助教提供的文件存储库，得分最高为 60%。**

| 得分项      |     分值 | 说明                              |
| ----------- | --------:| --------------------------------- |
| 正确性      |      55% | 通过所有公开数据点                |
| 鲁棒性      |      10% | 通过所有非公开数据点              |
| 开发文档    |      15% | 助教评分                          |
| Code Review |      20% | Git 仓库管理、代码规范等          |
| Bonus       | 最高 10% | 具体各项得分见 [bonus](#bonus)    |
| 总计        |     110% | 未通过正确性测试者 bonus 不能得分 |

### 时间表

助教将在固定时间节点检查学生的完成进度。如遇困难请**提前**联系助教。

- **Week 0** *（对应校历 2022-2023 学年第一学期第 12 周）*
  - 周三（11 月 30 日）：发布项目；
  - 周日（12 月 4 日 23:59 前）：提交开发文档（请填写此表单：<https://wj.sjtu.edu.cn/q/A2ATtW8r>）。
- **Week 1**
  - 周三（12 月 7 日）：上机课，检查开发文档；
  - 周日（12 月 11 日）：检查文件存储结构（块状链表）进度。
- **Week 2**
  - 周三（12 月 14 日 18:30 前）：**通过**文件存储数据结构正确性评测（[P1774](https://acm.sjtu.edu.cn/OnlineJudge/problem?problem_id=1774)）；
  - 周日（12 月 18 日）：检查主体逻辑部分进度。
- **Week 3**
  - 周三（12 月 21 日 18:30 前）：**通过**公开测试点评测（[P1075](https://acm.sjtu.edu.cn/OnlineJudge/problem?problem_id=1075)）；
  - 周日（12 月 25 日）：检查非公开测试点进度。
- **Week 4** *（对应校历第 16 周）*
  - 周三（12 月 28 日 18:30 前）：**通过**非公开测试点评测（[P1775](https://acm.sjtu.edu.cn/OnlineJudge/problem?problem_id=1775)），上机课后进行 code review。
    - Bonus 部分截止日期同主体逻辑，超时完成的部分不计分。

<!--
  - 周五 `12.31`：**通过**主体逻辑部分正确性测试
    - OJ 测试由两部分组成：[公开数据与基础鲁棒性评测 (P1075)](https://acm.sjtu.edu.cn/OnlineJudge/problem?problem_id=1075)； [里数据评测 (P1411)](https://acm.sjtu.edu.cn/OnlineJudge/problem?problem_id=1411)
    - 所有学生完成 Code Review
    - Bonus 成果展示
-->

**友情提醒：期末考试总是要好好备考的，所以请务必不要留给第 16 周的自己太多工作量。**

## 项目说明

### 开发要求

#### 开发文档

每位学生均需完成一份开发文档。开发文档格式无硬性要求，推荐使用 Markdown 书写，也可以使用 $\LaTeX$ 或 Microsoft Word 等格式。

开发文档内容**无硬性要求**，内容可以参考以下条目：

- 项目名称 / 文档作者
- 程序功能概述
- 主体逻辑说明
- 代码文件结构，即 `main` 函数与各个类的关系
- 各个类的接口及成员说明
- 文件存储说明
- 其他补充说明

如果最后提交代码不符合开发文档则会酌情扣分。合理的文档修订是允许的，但请写明修订记录。

#### Git 版本管理

你需要了解版本库、工作区、暂存区等 git 基础概念，并掌握 git 的常用指令，详见 [wiki](https://acm.sjtu.edu.cn/wiki/Programming_2022/Git) 和 [上机课 slides](https://invalid)。

你需要合理使用 commit 功能维护代码版本。具体来说：

- Commit 频率不可以太低（例如，不可以整个项目只有三四个 commit）；
  - 频繁的 commit 有助于细致地保存代码变更的历史。
- Commit message 内容可以清晰简要但不能缺失、不能是无意义内容。
  - 对于比较大的 commit，鼓励用多行的 commit message 具体描述干了什么；
  - 合理的 message 示例：
    - docs: clarify design reasoning and details
    - partial implementation of unrolled linked list
    - fix: 切换帐户之前检查权限
  - 不合理的 message 示例：
    - update
    - Add files via upload
    - Update README.md
    - bugfix *（具体修了什么？）*
    - 20221201 *（git 会自动存储 commit 时间，不用在 commit message 里说明。）*

你的 git 仓库需要整体文件结构清晰，了解并自主设置 `.gitignore` 等文件，保证编译产物（`./code`、`cmake-build-debug` 等）和下发的测试数据点不进入 git 仓库。Git repository 总大小（包括 `.git` 文件夹在内的 worktree）不得超过 5 MiB。

违反者会在 code review 中被扣分。

#### 代码风格

选择合适的代码风格，严格遵守选定风格的代码规范。详情见 [代码风格 wiki 页面](https://acm.sjtu.edu.cn/wiki/Programming_2022/%E4%BB%A3%E7%A0%81%E9%A3%8E%E6%A0%BC)。

### 业务需求

见 [业务需求文档](requirements.md)。

### Bonus

见 [bonus 文档](bonus.md)。

### 扣分

请保证自己项目结构的可读性，可以包括优化项目结构、适当的文件树指南等，晦涩难懂的项目可能会加大助教的工作量，也可能会影响你的成绩。

如有出现任何抄袭现象按 0 分计。
