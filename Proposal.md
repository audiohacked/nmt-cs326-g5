# Team 5 - Universal File Transfer Client #
# Project Proposal & Plan #

## Introduction ##
Although many file distribution platforms exist in modern computing, there is a notable lack of any universal, general purpose platform for file transfer.  Notable platforms currently in operation include Valve's Steam platform, which distributes and sales games and related media files on the Windows operating system, as well as less centralized but still popular file transfer applications like Kazaa or bit torrent clients.  While these platforms facilitate file distribution and content promotion very well, they are not general purpose and are often exclusive to an operating system, architecture, or file transfer protocol.

### Project Overview and Statement of Proposal ###
The project aims to provide a universal, intuitive, and streamlined method for retrieving files in an efficient manner.  We propose to develop a client application which facilitates file distribution.  This client will be cross-platform, running on the Windows, Linux, and OS X operating systems.  The client will also support mainstream file transfer protocols in a seamless manner.

### Project Scope and Objectives ###
The project's primary goal is to produce a client application which facilitates file transfer and runs on Windows, Linux, and OS X.  The client aims to use as much portable code as possible; maintaining cross-platform capability is a primary objective.
The client will support two file transfer protocols seamlessly, namely HTTP and bit torrent.  If time permits, the client will also aim to support FTP as well.  In addition, the client will report to a centralized database with information concerning file transfers in order to report statistics and other information about file downloads and the client itself.

## Risk Management Strategy ##
### Risk Table ###
| **Risks** | **Category** | **Probability** | **Impact** | **RMMM** |
|:----------|:-------------|:----------------|:-----------|:---------|
| Maintaining cross-platform code | TE, DE, PR | medium-high | Critical | Use of cross-platform libraries and strategies |
| Three separate client applications become disparate | PS, DE, TE | medium | Critical | Use of cross-platform code, peer review, and constant integration |
| Team member leaves | ST | low | Critical | Redistribute workload |
| Project is behind schedule | PR, CU, BU | medium | Marginal | Increase work-hours and meeting times |
| Member falls behind | ST | medium | Marginal | Redistribute workload, possibly increase meeting times |
| Hardware for targeted platform is unavailable | TE, DE | low | Negligible | Find alternative machines or use TCC |


**Category values**:
  * PS – Product Size Risk
  * BU – Business Impact Risk
  * CU – Customer Relations Risk
  * PR – Process Risk
  * TE – Technology Risk
  * DE – Development Environment Risk
  * ST – Risk Associated with Staff Size and Experience

**Impact values**:
  1. – catastrophic
  1. – critical
  1. – marginal
  1. – negligible


### Discussion of Risks to Be Managed ###
The primary risk in this project is not maintaining cross platform code.  The more platform-dependent code becomes a part of the project, the difficulty in developing the client increases as a platform-specific solution must be found for other operating systems; maintaining each client becomes more difficult as well.  The probability of this occurring is not negligible, and thus this critical risk must constantly be monitored during the course of the project.
Other risks for the project are less catastrophic, and include relatively common occurrences such as machine unavailability or a member falling behind on their work. Though the probability of these risks occurring ranges from improbable to highly probable, their impact to the project is mostly negligible with adequate mitigation strategies.

### Risk Mitigation, Monitoring, and Management Plan ###
#### Risk Mitigation ####
Minor risks related to scheduling and project progress will be avoided by maintaining consistent communication between all project members via a Google Group with a related Google Code repository.  Through these tools, members will discuss all aspects of the project and also have a central repository for project code and documents.  In addition, regular weekly meetings will be held in person with all group members.

The cross-platform code risk is more delicate, and must be avoided by having constant diligence towards the issue during the entire design and implementation phases of the project.  This risk will primarily be dealt with through the use of cross-platform libraries, but situations may arise in which there is no obvious cross-platform solution to a problem; in this case, the group will come together and discuss further mitigation options.  In addition, early experimentation and testing of these libraries with small projects and prototypes will take place among all team members as a side task during the requirements phase of the project so as to gain familiarity with tools before entering the design phase.

#### Risk Monitoring ####
By maintaining communication and holding weekly meetings, group members will give essentially continuous progress reports on their work.  This method will make the process of scheduling and progress risk monitoring fairly simple and rapid.  Peer review of code and constant integration of code changes as well as a collaborative, researched design plan will help in the monitoring of the cross-platform project risks.

#### Risk Management (Contingency Plans) ####
The scheduling, progress, and individual member risks will be managed via team discussion and resolutions.  In the case that progress of the project or an individual member becomes an issue, tasks may be redistributed or more meetings held, perhaps even with the purpose of dedicated, collaborative development.  Teamwork will be essential in managing these risks should they become serious problems.

If the cross-platform risk becomes a serious problem, the team will meet and discuss solutions, trying first to find alternatives which are platform-independent.  If no cross-platform solution can be found for a given problem, the team will assign the tasks of creating a minimized platform-specific solution for each client.

## Schedule ##
Below is a list of tasks associated with the project, a Gantt chart depicting task durations, dependencies and completion dates, and a summary of resource assignments for each task.

### Task List ###
  1. Requirement Specification and Analysis
  1. Programmatic Experimentation
    1. Sample Projects w/ wxWidgets
    1. Simple Prototypes
  1. Design Specification
    1. Cross-platform Backend Design
    1. Universal GUI Design
    1. File Transfer Protocols
    1. Database Schema
  1. Implementation
    1. System Framework
    1. GUI w/ wxWidgets
    1. File Transfer
    1. Platform-specific Code
    1. Database Reporting
  1. Testing
  1. Final Documentation

### Timeline Chart ###
http://nmt-cs326-g5.googlecode.com/files/ganttchart.JPG

### Resource Table ###
| **Task** | **People** | **Hardware & Software** | **Special** |
|:---------|:-----------|:------------------------|:------------|
|Requirement Specification and Analysis| All | N/A | N/A |
|Programmatic Experimentation| All | All (Listed Below) | N/A |
|Design Specification| All | N/A | N/A |
|Implementation - System Framework | All | Windows/Linux/Mac | N/A |
|Implementation - GUI| Sean, Josh, Corey | wxWidgets | N/A |
|Implementation - File Transfer| Sean, Josh, Adam, Kensie | All | N/A |
|Implementation - Platform-specific Code| All | All | N/A |
|Implementation - Database Reporting| Sean, Josh, Corey | SQLite/mySQL | Temporary Server|
|Testing| All | All | N/A|
|Documentation| All | N/A | N/A |

## Project Resources ##

### People ###
  1. Sean Nelson - Project Leader, Documentation, Developer
  1. Joshua Barron - Documentation, Developer
  1. Corey Brown - Developer
  1. Adam Troemner - Developer
  1. Kensie Sturdevant - Developer

### Hardware and Software Resources ###
#### Software ####
  * wxWidgets
  * Subversion
  * Google Code
  * CMake
  * DBMS software (Likely SQLite or mySQL)

#### Hardware ####
  * Linux
  * Windows 2000 to Windows Vista
  * Mac OS X 10.4 & 10.5

### Special Resources ###
  * Server for centralized content and database