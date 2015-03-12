# Digital Content Distribution and Publishing System #
## Team # 5 ##

# Design Specification #

## 1. Project Overview ##

The program will provide a cross-platform content distribution and publishing service. It will use a client-server model where the server will use and provide service through standard programs/services like Apache and MySQL. The customer can choose to use the server to distribute published files or allow users to upload their own content that can be sponsored/featured on the server.

The motivation for this project is the lack of a general-purpose, platform-independent content distribution service on the market.  Many content distribution services, such as Valve's Steam platform for game distribution, Apple's iTunes service for music distribution, or Netflix's online movie watching software, have some form of
platform-dependency (whether it be a an operating system or browser) and/or are content-specific; that is to say that they allow the distribution of only certain forms of digital content.


### 1.1 Scope and Objectives ###

The scope of the project is to build a base platform for customers to create a digital community and publishing system while also supporting at least Linux, Windows, and Mac users alike. The main function of the system is to provide an end-user a way to obtain any digital content, such as movies, music, and other entertainment. The system has to be fast, native-looking, and easily changeable/upgradeable. To insure the user's client is up to date, it will include an self updater. To facilitate downloading, the client will use `BitTorrent` and HTTP. Finally, the client can also be configured to include Community Portal and/or a web browser.

### 1.2 Supplementary Requirements ###

**FURPS Non-functional Requirements (Quality)**

_Usability_
  * Users familiar with other content distribution platforms and file transfer clients should feel at ease with this system.
  * User interface should always strive for simplicity and intuitiveness.
  * User interface should follow a tabbed system to divide functionality and reduce complexity.

_Reliability_
  * The entire system must be robust enough to handle common networking issues like dropped connections, missing files, and transfer errors.
  * User authentication system should use common security practices.

_Performance_
  * File transfers should initiate within two seconds of a client's request.
  * Content server should responsibly manage available bandwidth to achieve optimal browsing and transfer speeds.

_Supportability_
  * Content server's closed website system should be mostly dynamic, adapting to file additions/removals as well as changes in existing files' properties.

_Portability_
  * The application should be portable to many different operating systems, including Linux, Mac OS, and Microsoft Windows.

**FURPS+ Additional Non-functional Requirements (Constraints)**

_Implementation_
  * The client will be implemented in C++, utilizing the wxWidgets library as well as the libtorrent library for cross-platform code.


---


## 2. Customer Requirements ##
**Use-Case Diagram - Entire System**

_Note: This diagram was left unmodified from the Requirements Analysis for the purpose of readability, but the Server and Database packages should be grouped under a larger 'Server Functionality' package, and the Exception and Core packages under a 'Client Functionality' package._

![http://nmt-cs326-g5.googlecode.com/files/usecasev2_2.jpeg](http://nmt-cs326-g5.googlecode.com/files/usecasev2_2.jpeg)

**Actor Descriptions and Use-Cases by Actor**

`BasicUser` - the target audience for downloads, uses the client software.

![http://nmt-cs326-g5.googlecode.com/files/UseCase_BasicUser.jpeg](http://nmt-cs326-g5.googlecode.com/files/UseCase_BasicUser.jpeg)


---


`ContentDistributor` - the manager of the Centralized Content Server, inherits functionality from Basic User.

![http://nmt-cs326-g5.googlecode.com/files/UseCase_ContentDistributor.jpeg](http://nmt-cs326-g5.googlecode.com/files/UseCase_ContentDistributor.jpeg)


---


`DBManager` - provides storage and retrieval for information on downloads. This includes file location, file attributes, statistics including number of downloads, and other vital information.

![http://nmt-cs326-g5.googlecode.com/files/UseCase_Database.jpeg](http://nmt-cs326-g5.googlecode.com/files/UseCase_Database.jpeg)


---


`ContentServer` - communicates with the client software and the database. Is responsible for communication between client and database.

![http://nmt-cs326-g5.googlecode.com/files/UseCase_ContentServer.jpeg](http://nmt-cs326-g5.googlecode.com/files/UseCase_ContentServer.jpeg)


---


`Tracker` - communicates with the client software during a torrent download to provide connection information to peers.

![http://nmt-cs326-g5.googlecode.com/files/UseCase_Tracker.jpeg](http://nmt-cs326-g5.googlecode.com/files/UseCase_Tracker.jpeg)


---

**Use Case Descriptions**

Specific use case descriptions and sequence diagrams:

_Use Case Name_      **`DownloadFile`** _(Also applies to **'DownloadHTTPFile'**)_

_Participating Actors:_

Initiated by `BasicUser`

Communicates with `ContentServer`

_Flow of events:_

1. `BasicUser` chooses a file to download in file browser

2. `Client` software queries server to status of file

> 3. `ContentServer` responds with status of file

4. `Client` downloads file if available, using the appropriate protocol

_Entry Condition_
  * The user initiates a download

_Exit Condition_
  * The download completes successfully
  * The download is canceled by the user
  * There is a download error and the download cannot continue

_Quality Requirements_
  * The `ContentServer` and `Client` must communicate within a certain amount of time.


---


_Use Case Name_        **`DownloadTorrentFile`**

_Participating Actors:_

> Initiated by `BasicUser`

> Communicates with `ContentServer`, `DBServer`, `Tracker`

_Flow of events:_

1. `BasicUser` selects file in file browser portion of program

2. `BasicUser` selects download

3. Client sends out a request to the `ContentServer` for the .torrent file

> 4. `ContentServer` queries `DBServer` as to the status of the file

> 5. `DBServer` returns status of .torrent file to `ContentServer`

> 6. `ContentServer` returns status of .torrent file to `BasicUser`

7. If .torrent file is available, `Client` downloads it from `ContentServer`

8. `Client` performs checksum on .torrent file to make sure it was transferred successfully

9. `Client` queries `Tracker` for list of other clients with file or files defined
by .torrent file

  1. . `Tracker` returns list of clients if it exists, error if not

  1. . `Tracker` adds client to list of clients downloading file

12. `Client` queries other clients to find out who had what pieces of file or files

  1. . Other clients reply and specify what data is available for download

14. `Client` downloads files piece by piece

_Entry Condition_
  * `BasicUser` selects a download package in the interface that includes a torrent file

_Exit Condition_
  * Download completes, all files reside on local hard drive. OR
  * Download is cancelled by user. OR
  * There is a fatal download error

_Quality Requirements_
  * All servers will respond within a certain amount of time, determined by server settings.


---


_Use Case Name_      **`ReportFileDownload`**

_Participating Actors_

Participated in by `BasicUser`

Communicates with `ContentServer`

Communicates with `DBManager`

_Flow of Events:_

  1. `Client` completes a `BasicUser` initiated sponsored file download, opens connection with `ContentServer`.

2. `ContentServer` attempts to open a connection to `DBManager`, if it is not already open, and notifies the `Client` to send data

> 3. `Client` sends file download statistics concerning the recent file transfer (completion time, average speed, incrementing the total number of downloads recorded, etc.) to `ContentServer`.

4. `ContentServer` sends an update/insert command to the `DBManager`

5. `DBManager` performs the queries and commits changes to database.

6. `DBManager` notifies `ContentServer` of completion, `ContentServer` notifies `Client`

> 7. `Client` closes connection to `ContentServer`.

_Entry Condition_
  * The user completes a download

_Exit Condition_
  * The database is updated
  * The database does not respond

_Quality Requirements_
  * The operation must complete within 30 seconds


---


_Use Case Name_  **`ReportFileUpload`**

_Participating Actors_
Participated in by `BasicUser`
Communicates with `ContentServer`
Communicates with `DBManager`

_Flow of Events:_

  1. `Client` completes a `BasicUser` initiated sponsored file upload, opens connection with `ContentServer`.

2. `ContentServer` attempts to open a database connection, if it is not already open, and notifies the `Client` to send data

> 3. `Client` sends file upload statistics concerning the recent file transfer (size of file, type of file, description of file, a human readable name of the file, etc.) to `ContentServer`.

4. `ContentServer` sends an update/insert command to the `DBManager`

5. `DBManager` performs the queries and commits changes to database.

6. `DBManager` notifies `ContentServer` of completion, `ContentServer` notifies `Client`

> 7. `Client` closes connection to `ContentServer`.

_Entry Condition_
  * The user completes a sponsored file upload

_Exit Condition_
  * The database is updated
  * The database does not respond

_Quality Requirements_
  * The operation must complete within 30 seconds


---


_Use Case Name_  **`UploadFile`**

_Participating Actors_
Communicates with `ContentServer`
Initiated by `BasicUser` or `ContentDistributor`

_Flow of Events:_

  1. `BasicUser` or `ContentDistributor` selects a file to upload.


> 2. `Client` opens connection (if necessary) with the `ContentServer`.

> 3. `Client` transfers file or files to `ContentServer` over HTTP.

> 4. `ContentServer` connects to `DBManager` if not already connected

> 5. `ContentServer` dynamically updates appropriate pages to reflect new content.

_Entry Condition_
  * `BasicUser` or `ContentDistributor` who initiated the upload has upload privileges

_Exit Condition_
  * The database is updated
  * The database does not respond

_Quality Requirements_
  * A connection must be maintained between the `Client` and the `ContentServer` at all times


---


_Use Case Name_  **`DesignateFileSponsoredStatus`**

_Participating Actors_
Communicates with `ContentServer`
Initiated by `ContentDistributor`

_Flow of Events:_

1. `ContentDistributor` selects a file which is to have it's sponsored status modified.

2. `Client` opens connection with `ContentServer`, queries the sponsored status of the selected file.

> 3. `ContentServer` connects with and queries `DBManager`

4. `ContentDistributor` is given the option to modify this status.

> 5. If changed, the new status is committed to the database by `ContentServer`.

6. Client closes connection to `ContentServer`.

_Entry Condition_
  * `ContentDistributor` who initiated the operation has administrator privileges

_Exit Condition_
  * The database is updated
  * The database does not respond
  * `ContentDistributor` cancels request

_Quality Requirements_
  * A connection must be maintained between the `Client` and the `ContentServer` at all times


---


_Use case name_  **`GetFileStatistics`**

_Participating Actors_

Initiated by `BasicUser` or `ContentServer`

Communicates with `ContentServer`, `Database`

  1. `BasicUser` queries `ContentServer` or `ContentServer` opens a connection with `DBManager` and queries statistics (number of downloads per day, month, year, or total, popularity rating, sponsored status, etc.) about a given file.
  1. `DBManager` completes the requested query and serves data to user or server.
  1. Connection between `BasicUser`/`ContentServer` is closed.


---


_Use case name_  **`ReportTransferProgress`**

_Participating Actors_

initiated by `BasicUser`

_Flow of Events_

  1. `BasicUser` selects a file (or merely is transferring a file) for which transfer information (% completed, number of bytes downloaded, transfer speed, etc.) is desired.
  1. `Client` calculates transfer information and displays it to the user (often continuously).


---


_Use case name_  **`BrowseContentSite`**

_Participating Actors_

> Initiated by `Basic User`

> Communicates with `ContentServer`

**Flow of Events**

  1. `BasicUser` requests a page via the in-house browser from the `ContentServer`.

> 2. `ContentServer` receives request and serves page to client.

> 3. `Client` renders page in browser.


---


_Use case name_  **`RemoveFile`**

_Participating Actors_
Initiated by `BasicUser`
Communicates with `ContentServer`, `DBManager`

  1. `BasicUser` selects a file for deletion.

> 2. `Client` sends delete request to content server.

> 3. `ContentServer` removes file and any related information, opens a connection to the `DBManager` and sends a corresponding delete (this may actually be an archival rather than a physical deletion) query for the file's database entries.

> 4. `DBManager` completes query, `ContentServer` reports success to `Client`.

> 5. `Client` reports success to user.

_Entry condition_
  * `BasicUser` has rights over the file for deletion or is a `ContentDistributor`.

_Exit condition_
  * File is successfully deleted by `ContentServer`
  * File's information is successfully deleted from database by `DBManager`
  * There is a fatal error and the operation cannot continue

_Quality requirements_
  * The user interface must provide an "are you sure" dialogue to the user


---


_Use case name_  **`SetClientPreferences`**

_Participating actors_

Initiated by `BasicUser`

_Flow of Events_

  1. `BasicUser` selects to edit their preferences from a drop-down menu.
  1. `Client` opens a preferences dialog.
  1. `BasicUser` changes their preferences.
  1. `Client` commits preferences to memory and applies any immediately relevant changes.
  1. `Client` closes preferences dialog.


---


_Use case name_  **`SetServerPreferences`**

_Participating Actors:_

Initiated by `ContentDistributor`

Communicates with `ContentServer`

_Flow of Events_

  1. `ContentDistributor` edits server preferences via configuration file.
  1. `ContentServer` reads and implements changed preferences.



---


_Use Case Name_        **`AbortFileTransfer`**

_Participating Actors_

Initiated by `BasicUser`

_Flow of events_

1. `BasicUser` clicks the cancel button in the interface

> 2. `Client` responds with a message asking the user if they are sure

3. If `BasicUser` clicks yes, the client software deletes the partially downloaded file

4. The `Client` software then removes the download from the list of downloads

_Entry Condition_
  * The `BasicUser` is downloading a file or files.

_Exit Condition_
  * The `Client` successfully deletes the partially downloaded files and removes the downloads from the list of active downloads. OR
  * The `BasicUser` clicks "no" in the confirmation dialogue box, thereby cancelling the cancellation.
_Quality Requirements_
  * The dialogue box only appears for 10 seconds, before the cancellation is automatically cancelled.



---

_Use case name_ **`ExTransferError`**

_Participating Actors:_ `ContentServer` and/or `Tracker`, `BasicUser`

_Flow of events_

  1. Serving actor (`ContentServer` or `Tracker`) reports an error and logs it.

> 2.   Serving actor attempts to resolve error while determining the error type.

> 3.   If the error type is determined, its appropriate use case is invoked.

> 4.   Error is reported to `Basic User`

_Entry conditions_

  * A transfer error has occurred.

_Exit conditions_

  * The error is logged, reported, and resolved if possible.


---

_Use case name_ **`ExFileNotFoundError`**

_Participating Actors:_ `ContentServer`, `BasicUser`

_Flow of events_

  1. `ContentServer` reports error.

> 2.   Error reported to `BasicUser`.

_Entry conditions_

  * `BasicUser` has requested a file that the server could not locate


---


_Use case name_ **`ExTorrentTransferError`**

_Participating Actors:_ `Tracker`, `BasicUser`

_Flow of events_

  1. `Client` detects an error with a torrent transfer.

> 2.   `Client` reports error to `BasicUser`.

> 3.   `Client` asks `BasicUser` to either retry download or to delete torrent file and/or downloaded files.

> 4.   `Client` deletes files as necessary.

_Entry conditions_

  * `BasicUser` is downloading torrent and an error occurs.

_Exit conditions_

  * Data is deleted
  * `BasicUser` selects retry download

_Quality requirements_

  * `Client` must only delete files pertaining to the affected download
  * Minor issues (particularly temporary connection issues) must be dealt with automatically


---


## 3. Architectural Design ##

Our project is utilizing the Model-View-Controller (MVC) architecture to effectively reduce complexity and separate application entities (files, database storage) from business logic (file transfer) and boundary entities (user interface).

Other architectures were considered, including the Client-Server model and Peer-To-Peer model, but these architectures only encompass part of the functionality of application.  We have, however, adhered to many of the guiding principles behind these architectures while structuring our application under MVC.

### 3.1 Subsystem Architecture ###

This section should include a subsystem dependency diagram and supporting discussion.
![http://nmt-cs326-g5.googlecode.com/files/subsystem_architecture_v1.jpeg](http://nmt-cs326-g5.googlecode.com/files/subsystem_architecture_v1.jpeg)

This diagram is divided into three distinct layers; model, view, and controller.  Following the MVC architecture and philosophy, subsystems performing boundary actions are in the view layer.  These subsystems consist of the User Interface (composed of the GUI and in-house web browser subsystems) and the Server subsystem.  The User Interface handles virtually every interaction with the user, the Server subsystem represents the centralized content server with which the client interacts.

The controller layer consists of subsystems which perform the vast majority of business logic for the application.  This layer contains the wxWidgets, Transfer Manager, Database Manager, and Content Manager subsystems.  The wxWidgets system represents the wxWidgets API, which allows our application to be platform-independent and is responsible for rendering the client and implementing the web browser.  The Transfer Manager is an abstract subsystem, realized by two subsystems, the HTTP Transfer Manager and the Torrent Transfer Manager, which handle and implement the code to perform transfers over their respective protocols between clients and the centralized content server, as well as between clients (in the case of a torrent transfer) and a tracker.  The Database Manager subsystem is responsible for handling requests from both client and server concerning the centralized database, as well as connecting to and performing transactions with that database.  Finally, the Content Manager subsystem is a server-side subsystem which manages requests for files from clients.  The Content Manager also provides the necessary functionality to perform user authentication and administrative actions for users who are "Content Distributors".

The lowest level of the architecture is the model layer, and is comprised of only three subsystems; an OS-specific GUI Library, the Local File System, and a mySQL Database.   The OS-specific GUI Library is a dynamic system, controlled by the wxWidgets subsystem to perform rendering actions on a specific operating system.  The internal class hierarchy related to these subsystems follows a bridge design pattern for separating the implementation of GUI concepts (windows, menus, dialogs, etc.) from an OS-specific implementation of those concepts.  The second subsystem, the Local File System, is also a generic subsystem which is largely implemented by system API's.  This subsystem is responsible for storing files which are downloaded to clients and uploaded by clients to the content server.  Finally, the third subsystem, the mySQL Database, consists of the actual relational schema and physical tables of application data in the mySQL DBMS.  This subsystem is controlled exclusively by the Database Manager subsystem.


### 3.2 Deployment Model ###

http://nmt-cs326-g5.googlecode.com/files/deployment_diagram_v2.JPG

The deployment model for the application is fairly traditional; client-side systems are mapped to the client executable, server systems (Content Manager) are mapped to a server side applet, and the database subsystem is mapped to a mySQL database.  One content server supports many clients, and one database instance is tied to one server.


---


## 4. Use Case Realization Design ##

Specific use case descriptions and sequence diagrams:

_Use Case Name_      **`DownloadFile`** _(Also applies to **'DownloadHTTPFile'**)_

**Sequence Diagram**

![http://nmt-cs326-g5.googlecode.com/files/seq_abstractdownload.jpeg](http://nmt-cs326-g5.googlecode.com/files/seq_abstractdownload.jpeg)

**Interaction Diagram**

![http://nmt-cs326-g5.googlecode.com/files/downloadFileClassDiagram.png](http://nmt-cs326-g5.googlecode.com/files/downloadFileClassDiagram.png)

This generic use case includes all more specific download use cases, which include HTTP and Torrent downloads, at this time. The Basic User selects the download in the GUI (often through the in-house web browser), which then communicates the request for the download to the client's proper `TransferManager` object, which is specific to each type of transfer. The manager then initiates a connection with the server to be downloaded from, using information from the `ContentManager` object residing on the content server.


---


_Use Case Name_        **`DownloadTorrentFile`**

**Sequence Diagram**

![http://nmt-cs326-g5.googlecode.com/files/seq_downloadtorrentfile.jpg](http://nmt-cs326-g5.googlecode.com/files/seq_downloadtorrentfile.jpg)

**Interaction Diagram**

![http://nmt-cs326-g5.googlecode.com/files/downloadTorrentFileClassDiagram.png](http://nmt-cs326-g5.googlecode.com/files/downloadTorrentFileClassDiagram.png)

The user selects a file or set of files to download, which are associated with the torrent download type. The GUI then communicates the download request to the Torrent Transfer Manager, which then communicates with the `ContentManager` object to retrieve the torrent file. The Torrent Transfer Manager then interprets the torrent file and the location of the torrent tracker. The Torrent Transfer Manager then communicates with the torrent tracker and receives the location of peers with the desired download.



---


_Use Case Name_      **`ReportFileDownload`**

**Sequence Diagram**

![http://nmt-cs326-g5.googlecode.com/files/seq_reportfiledownload.jpeg](http://nmt-cs326-g5.googlecode.com/files/seq_reportfiledownload.jpeg)

**Interaction Diagram**

![http://nmt-cs326-g5.googlecode.com/files/reportFileDownloadClassDiagram.png](http://nmt-cs326-g5.googlecode.com/files/reportFileDownloadClassDiagram.png)

The `ContentManager` checks to be sure it has an open connection to the `DBManager`, which manages the actual connection to the database. If the connection is ready, the `ContentManager` communicates its request to the `DBManager`, and then `DBManager` signals it is ready for the data. `ContentManager` then communicates the report of the file download, which is then inserted into the database. `DBManager` then reports to `ContentManager` with success or failure.


---


_Use Case Name_  **`ReportFileUpload`**

**Sequence Diagram**

![http://nmt-cs326-g5.googlecode.com/files/seq_reportfileupload.jpeg](http://nmt-cs326-g5.googlecode.com/files/seq_reportfileupload.jpeg)

**Interaction Diagram**

![http://nmt-cs326-g5.googlecode.com/files/ReportFileUploadClassDiagram.png](http://nmt-cs326-g5.googlecode.com/files/ReportFileUploadClassDiagram.png)

The `ContentManager` checks to be sure it has an open connection to the `DBManager`, which manages the actual connection to the database. If the connection is ready, the `ContentManager` communicates its request to the `DBManager`, and then `DBManager` signals it is ready for the data. `ContentManager` then communicates the report of the file upload, including the attributes and location of the file, which is then inserted into the database. `DBManager` then reports to `ContentManager` with success or failure.


---


_Use Case Name_  **`UploadFile`**

**Sequence Diagram**

![http://nmt-cs326-g5.googlecode.com/files/seq_uploadfile.jpg](http://nmt-cs326-g5.googlecode.com/files/seq_uploadfile.jpg)

**Interaction Diagram**

![http://nmt-cs326-g5.googlecode.com/files/UploadFileClassDiagram.png](http://nmt-cs326-g5.googlecode.com/files/UploadFileClassDiagram.png)

The authenticated user communicates a request to the `ContentManager` to upload a file. The `ContentManager` checks with the database if the user is allowed to upload files. If the user is properly authorized, they select the file type and location, and upload the file to the server. The user is prompted by the GUI for information pertaining to the file, and the content manager receives the file and other relevant information, and inserts the proper data into the database through the `DBManager`.


---


_Use Case Name_  **`DesignateFileSponsoredStatus`**

**Sequence Diagram**

![http://nmt-cs326-g5.googlecode.com/files/seq_designatefilesponsoredstatus.jpg](http://nmt-cs326-g5.googlecode.com/files/seq_designatefilesponsoredstatus.jpg)

**Interaction Diagram**

![http://nmt-cs326-g5.googlecode.com/files/designateFileSponsoredStatusClassDiagram.png](http://nmt-cs326-g5.googlecode.com/files/designateFileSponsoredStatusClassDiagram.png)

An authenticated user uses the GUI to select a file that they want to designate the sponsored status upon. The GUI then contacts the `ContentManager`, which then checks with `DBManager` to make sure the user is a Content Distributor. If the user is a Content Distributor, then the original request is carried out by the `ContentManager`, which sends the proper command to the `DBManager`.


---


_Use case name_  **`GetFileStatistics`**

**Sequence Diagram**

![http://nmt-cs326-g5.googlecode.com/files/seq_getfilestatistics.jpg](http://nmt-cs326-g5.googlecode.com/files/seq_getfilestatistics.jpg)

**Interaction Diagram**

![http://nmt-cs326-g5.googlecode.com/files/GetFileStatisticsClassdiagram.png](http://nmt-cs326-g5.googlecode.com/files/GetFileStatisticsClassdiagram.png)

The `ContentManager` requests file statistics through the `DBManager`, which has the actual connection to the database. The `DBManager` responds with either the data or an error code.

---


_Use case name_  **`ReportTransferProgress`**

**Sequence Diagram**

http://nmt-cs326-g5.googlecode.com/files/seq_reporttransferprogress2.JPG

**Interaction Diagram**

![http://nmt-cs326-g5.googlecode.com/files/ReportTransferProgressClassD.png](http://nmt-cs326-g5.googlecode.com/files/ReportTransferProgressClassD.png)

The GUI requests the progress of a transfer from a specific `TransferManager`. The `TransferManager` returns the progress (an integer from 0-100) or an error message.

---


_Use case name_  **`BrowseContentSite`**

**Sequence Diagram**

![http://nmt-cs326-g5.googlecode.com/files/seq_browsecontent.jpeg](http://nmt-cs326-g5.googlecode.com/files/seq_browsecontent.jpeg)

**Interaction Diagram**

![http://nmt-cs326-g5.googlecode.com/files/browseContentSiteClassDiagram2.png](http://nmt-cs326-g5.googlecode.com/files/browseContentSiteClassDiagram2.png)

This use case covers the in-client web browsing of the centralized content server.  Essentially, a user requests a particular web page; the GUI relays the request to the `ContentManager` class, which then returns the requested data to the client, which is then rendered by the GUI.

The interaction diagram involves two classes; the GUI and the `ContentManager`.  The multiplicity of this relationship merely indicates that one `ContentManager` can service multiple GUI's (client applications).


---


_Use case name_  **`RemoveFile`**

**Sequence Diagram**

![http://nmt-cs326-g5.googlecode.com/files/seq_removefile.jpg](http://nmt-cs326-g5.googlecode.com/files/seq_removefile.jpg)

**Interaction Diagram**

![http://nmt-cs326-g5.googlecode.com/files/removeFileClassDiagram2.png](http://nmt-cs326-g5.googlecode.com/files/removeFileClassDiagram2.png)

An authenticated user makes a request to the Content Manager through the GUI to remove a download from the server. The Content Manger communicates with the `DBManager` and confirms that the user is allowed to delete files from the server. The Content Manager then sends the request to the `DBManager` to delete the file information, and, if successful, deletes the actual file. If unsuccessful, an error message is returned to the GUI and displayed to the user.


---


_Use case name_  **`SetClientPreferences`**

**Sequence Diagram**

![http://nmt-cs326-g5.googlecode.com/files/seq_setclientpreferences.jpeg](http://nmt-cs326-g5.googlecode.com/files/seq_setclientpreferences.jpeg)

**Interaction Diagram**

![http://nmt-cs326-g5.googlecode.com/files/SetClientPreferencesClassDiagram.png](http://nmt-cs326-g5.googlecode.com/files/SetClientPreferencesClassDiagram.png)

A basic user selects a 'preferences' menu item in the GUI. The GUI then initializes the preference dialog, which reads the user's preferences from a local configuration file. The user can then change their preferences through the preference dialog, which can then be saved.


---


_Use case name_  **`SetServerPreferences`**

**Sequence Diagram**

![http://nmt-cs326-g5.googlecode.com/files/seq_setserverpreferences.jpeg](http://nmt-cs326-g5.googlecode.com/files/seq_setserverpreferences.jpeg)

**Interaction Diagram**

![http://nmt-cs326-g5.googlecode.com/files/SetServerPreferencesClassDiagram.png](http://nmt-cs326-g5.googlecode.com/files/SetServerPreferencesClassDiagram.png)

An authenticated Content Distributor selects the option to set the server preferences in the GUI. The GUI then communicates the request to the `ContentManager`. The `ContentManager` then contacts the `DBManager` to see if the user is in fact a Content Distributor. If the user is allowed to edit the server preferences, the `ContentManager` notifies the GUI and a modified Preference Dialog is initialized. The Content Distributor can then edit various settings and commit them to the `ContentManager`, or cancel the process.


---


_Use Case Name_        **`AbortFileTransfer`**

**Activity Diagram**

![http://nmt-cs326-g5.googlecode.com/files/act_aborttransfer.jpeg](http://nmt-cs326-g5.googlecode.com/files/act_aborttransfer.jpeg)

**Interaction Diagram**

![http://nmt-cs326-g5.googlecode.com/files/abortFileTransferClassDiagram.png](http://nmt-cs326-g5.googlecode.com/files/abortFileTransferClassDiagram.png)

A Basic User selects a download within the GUI and presses the cancel button. The GUI then communicates with the proper transfer manager (depending on the type of transfer), which then stops the download, deletes the file, and notifies the GUI, which in turn notifies the user.


---


## 5. Subsystem Design ##

_Note: Many of the internal interactions of these subsystems are described textually, though by referring to Section 4 (Use Case Realization), these interactions are often described graphically via the sequence diagram for the use case._

### 5.1 User Interface ###
This set of subsystems is comprised a series of classes, pictured below:

![http://nmt-cs326-g5.googlecode.com/files/Class%20Diagram%20-%20UI%20%28v2%29.jpeg](http://nmt-cs326-g5.googlecode.com/files/Class%20Diagram%20-%20UI%20%28v2%29.jpeg)

The subsystem's internal associations are depicted below:

![http://nmt-cs326-g5.googlecode.com/files/ssinteraction_ui_v1.jpeg](http://nmt-cs326-g5.googlecode.com/files/ssinteraction_ui_v1.jpeg)

The functionality of this class is described in terms of the next three subsystems of the User Interface.

**5.1.1 GUI**

This subsystem implements the graphical user interface via the wxWidgets libraries.  When the GUI class is invoked (via the invoke() method), it establishes all the necessary wxWidgets components and events to manage the graphical user interface.  In addition, methods like openPreferenceDialog() and initiateUpload() handle common boundary actions between users and the client.

_Class: GUI_

Attributes:
| **Name** | **Type** | **Description** |
|:---------|:---------|:----------------|
| gui\_menus | Menu | a container for a wxMenu object, which displays menus |
| gui\_notebook | Notebook | manages a wxNotebook object |
| gui\_webBrowser | `WebBrowser` | a container for the web browser portion of the GUI, which allows the user to browse the content on the server |
| gui\_Panel | Panel | provides an interface to attributes of the overall window |
| gui\_prefDialog | `PreferenceDialog` | handle to custom preferences dialog |

Methods:
| **Name** | **Description** |
|:---------|:----------------|
| openPreferenceDialog | instantiates a preference dialog and displays it to the user |
| initiateDownload | communicates a download request to the transfer manager subsystem |
| cancelDownload | communicates a download cancellation request to the transfer manager |
| initiateUpload | communicates an upload request to the transfer manager |
| cancelUpload | communicates an upload cancellation request to the transfer manager |
| exit | exit the program |
| authenticate | communicates an authentication request to the Content Manager Subsystem |

**5.1.2 Web Browser**

The Web Browser subsystem is handled by the `WebBrowser` class.  The primary operation contained in this class is the requestWebContent() method; this method handles the transfer of web content from the `ContentManager` class (see the Content Manager subsystem). The renderWebContent() method is primarily responsible for displaying web content via the in-house browser and passing along download requests to other subsystems via methods like initiateDownload().  This class subclasses the wxMozilla class, which implements Mozilla web functionality within the wxWidgets library.

_Class: `WebBrowser`_

Attributes:
| **Name** | **Type** | **Description** |
|:---------|:---------|:----------------|
| contentServerIP | String | Represents the location of the Remote Content Server control object |

Methods:
| **Name** | **Description** |
|:---------|:----------------|
| requestWebContent | communicates a request through the Remote Content Server control object for html type content related to downloads |
| renderWebContent | displays content to the user |
| connect | connects to the Remote Content Server control object |
| disconnect | disconnects from the Remote Content Server control object |

**5.1.3 wxWidgets**

The wxWidgets subsystem represents the wxWidgets library, which the application makes heavy use of in order to create a cross-platform client which maintains the "look and feel" of a native application.  The GUI class is essentially a wrapper class which loosely  follows an adapter and bridge pattern with the wxWidgets library, though this interaction is not depicted because the class structure of the library is very complex and non-essential to this application's design.

Many of the aggregated classes (like Menu, Window, Panel, etc.) of the master GUI classes are wrappers to wxWidget classes.  All these classes implement the Window interface (which in turn generalizes the wxWindow class) in order to reduce system coupling.

The following is a brief overview of the most important classes used from the wxWidgets library:

_Classes/interfaces:_
| **Name** | **Description** |
|:---------|:----------------|
| wxMenu | "A menu is a popup (or pull down) list of items, one of which may be selected before the menu goes away (clicking elsewhere dismisses the menu). Menus may be used to construct either menu bars or popup menus." |
| wxWindow | "wxWindow is the base class for all windows and represents any visible object on screen. All controls, top level windows and so on are windows. Sizers and device contexts are not, however, as they don't appear on screen themselves." |
| wxMozilla | "wxMozilla is a project to develop a wxWindows component for embedding the Mozilla browser into any wxWindows application. The wxMozilla classes use Mozilla's XPCOM (Cross Platrom COM) interface to embed a HTML browser or editor within the application." |
| wxPanel | "A panel is a window on which controls are placed. It is usually placed within a frame. It contains minimal extra functionality over and above its parent class wxWindow; its main purpose is to be similar in appearance and functionality to a dialog, but with the flexibility of having any window as a parent." |
| wxButton | "A button is a control that contains a text string, and is one of the most common elements of a GUI. It may be placed on a dialog box or panel, or indeed almost any other window." |
| wxDialog | "A dialog box is a window with a title bar and sometimes a system menu, which can be moved around the screen. It can contain controls and other windows and is usually used to allow the user to make some choice or to answer a question." |
| wxNotebook | "This class represents a notebook control, which manages multiple windows with associated tabs." |

All quotes taken from docs.wxwidgets.org

### 5.2 Transfer Manager ###

The Transfer Manager subsystem is comprised of several classes responsible for allowing access to the Torrent Transfer Manager and HTTP Transfer Manager easily.  The subsystem's classes are pictured below:

![http://nmt-cs326-g5.googlecode.com/files/Class%20Diagram%20-%20Transfer%20Manager.jpeg](http://nmt-cs326-g5.googlecode.com/files/Class%20Diagram%20-%20Transfer%20Manager.jpeg)

The subsystem's internal associations and remote connection to the content server are depicted below:

![http://nmt-cs326-g5.googlecode.com/files/ssinteraction_transfermanager.jpeg](http://nmt-cs326-g5.googlecode.com/files/ssinteraction_transfermanager.jpeg)

The primary object in this subsystem is the `TransferManager` interface, which all file transfer classes must realize in order to be compatible with the system.  In addition to reducing coupling, this allows for a large amount extensibility and generality of 'file transfer' within the system, as new classes which implemented file transfer over different protocols could easily be created.

The next most important objects are the HTTPTransferManager and the `TorrentTransferManager` classes, which will be discussed in sections 5.2.1 and 5.2.2, respectively.

The subsystem also defines the Download interface, which all file handling classes must realize in a similar manner to the `TransferManager` interface in order to handle local file transactions.  This section of the subsystem is the link the the Local File Storage subsystem in the Model section of the subsystem architecture.  The Download interface implements methods which are useful for reporting information about a file _transfer_, such as the current download speed or percentage completion.

In addition, all classes which implement the Transfer interface also aggregate the File class, which is a concrete object which has many attributes common to all files.

_Interface: `TransferManager`_

Attributes:
| **Name** | **Type** | **Description** |
|:---------|:---------|:----------------|
| activeTransfers | Transfer | contains the transfers that are actively downloading or uploading data |
| inactiveTransfers | Transfer | contains transfers that are not actively downloading or uploading data |

Methods:
| **Name** | **Description** |
|:---------|:----------------|
| startTransfer | initiates a transfer |
| cancelTransfer | stops a transfer in progress and deletes all files and objects associated with the transfer |
| pauseTransfer | temporarily suspends a transfer in progress |
| finishTransfer | notifies the Remote Content Server that the transfer has completed |
| invoke | initializes the transfer manager |
| destroy | destroys the transfer manager instance when exiting the program |


**5.2.1 HTTP Transfer Manager**

The HTTP Transfer Manager subsystem handles the transfer of files over the HTTP as well as any standard HTTP requests, such as HEAD and GET, that are required.

Pictured above, the HTTP Transfer Manager subsystem is comprised primarily of two classes: the HTTPTransferManager class and the HTTPTransfer class.

The HTTPTransferManager implements two additional methods: downloadFile() and uploadFile().  These methods are responsible for contacting the content server (the request is handled by the server-side Content Manager subsystem) and requesting or receiving a file.  The methods of the HTTPTransferManager interface are implemented in a manner that utilizes HTTP via the libcurl library, an open-source API for HTTP/S.  The sole interface to this library is the transferHandle attribute.

The HTTPTransfer class is a simple class which necessarily implements the Download interface. It implements one additional method, getFileName() which retrieves the name of the file associated with the object.

_Class: HTTPTransferManager_

Attributes:
| **Name** | **Type** | **Description** |
|:---------|:---------|:----------------|
| contentServerIP | Transfer | keeps track of the location of the content server |
| transferHandle | curlHandle | provides access to libcurl, which handles HTTP transfers |

Methods:
| **Name** | **Description** |
|:---------|:----------------|
| downloadFile | downloads a file from a specific location |
| uploadFile | uploads a file to the content server |

**5.2.2 Torrent Transfer Manager**

The Torrent Transfer Manager is responsible for managing the torrent transfers.  It will communicate with the tracker, the seeds, and the peers to efficiently transfer the torrents. This subsystem will also download and seed the torrent upon completion of the download.

Pictured above, the Torrent Transfer Manager subsystem is likewise comprised of primarily of two classes: the `TorrentTransferManager` class and the `TorrentTransfer` class.

The `TorrentTransferManager` implements two additional methods: downloadTorrent() and connectToTracker().  The downloadTorrent() method works similarly to the HTTPTransferManager's downloadFile() method, except it targets a torrent file on the content server.  Upon completion of the torrent file transfer, the class utilizes the connectToTracker() method to connect to the torrent file's designated tracker(s).  The `TorrentTransferManager` implements the Transfer Manager interface in such a way to manage the peer to peer connections of the `BitTorrent` protocol, using the libtorrent library.

The libtorrent library implements the `BitTorrent` protocol, and provides several useful objects which facilitate the transfer of file data in a torrent swarm.  The primary object is a session, which is aggregated by the `TorrentTransferManager`.  Individual torrent information objects, which store critical torrent information, such as peer and tracker IP addresses, are aggregated by the `TorrentTransfer` class.

The `TorrentTransfer` class realizes the Transfer interface, but also has many additional attributes.  These include an array of File objects (as a torrent download often contains several files), a handle to the associated libtorrent torrent object (torrentHandle), as well as a handle to the torrent's information (torrent\_info).

_Class: `TorrentTransferManager`_

Attributes:
| **Name** | **Type** | **Description** |
|:---------|:---------|:----------------|
| `FingerPrint` | fingerprint | imprinting attribute for client |
| transferHandle | curlHandle | provides an interface to libcurl for HTTP transfer of the .torrent files|
| torrentSession | Session | provides a handle to torrent sessions |
| sessionSettings | session\_settings | provides a handle to modify global torrent session settings |

Methods:
| **Name** | **Description** |
|:---------|:----------------|
| connectToPeers | connects to other clients downloading or seeding the specific transfer|
| downloadTorrent | initializes a torrent download |
| uploadTorrent | initializes a torrent upload |
| setTransferSpeed | changes maximum upload and download speeds |
| getSessionStatus | allows the retrieval of session information |

### 5.3 Database Manager ###
The Database Manager subsystem is a subsystem common to both the client and server applications, though each instance performs somewhat differently in the context of these different systems.  This system is responsible for connecting to a MySQL database as well as handling high-level (i.e., retrieving the top 10 downloads) and, internally, simple transactions (inserting a new record, for example) with the database.

The subsystem's internal associations are depicted here:

http://nmt-cs326-g5.googlecode.com/files/ssinteraction_db_2.JPG

Pictured below, the Database Manager subsystem is implemented as follows:

![http://nmt-cs326-g5.googlecode.com/files/Class%20Diagram%20-%20Database%20Manager.jpeg](http://nmt-cs326-g5.googlecode.com/files/Class%20Diagram%20-%20Database%20Manager.jpeg)

The `DBManager` associates itself with the wxODBC library via the dbHandle object, which is of type wxDB.  This class implements the fundamental protocols and functionality in order to perform database connections and transactions.  Every other method uses this handle to actually perform database operations.

The `DBManager` implements several important methods, the first of which are the dbConnect() and dbDisconnect() methods.  These methods connect to and disconnect from the database according to the connectionString and databaseType attributes.

The dbSelect(), dbInsert(), dbDelete(), and dbUpdate() methods implement the simple SQL transactions (SELECT, INSERT, DELETE, and UPDATE), respectively.  These methods are private, as the DBManager's purpose is to provide a high-level black-box interface to the application's database functionality.

The reportFileDownload() and reportFileUpload()/addFiletoDB()/addTorrenttoDB() methods alter the database to increment a download count on a particular file or create a new record for newly added content.  The designateFileSponsoredStatus() is a method used by Content Distributors (Administrative users and sometimes normal users) to set the sponsored flag on a file's record, which will then promote the file to "sponsored" status.

_Class: DBManager_

Attributes:
| **Name** | **Type** | **Description** |
|:---------|:---------|:----------------|
| connectionString | String | the string that is passed to the database driver to connect to the database |
| databaseType | String | the brand of database (mysql, oracle, etc.) |
| dbHandle | wxDB | the actual connection to the database |

Methods:
| **Name** | **Description** |
|:---------|:----------------|
| dbSelect | private method used to get records from the database using SELECT statements |
| dbInsert | private method used to put records into the database using an INSERT statement |
| dbDelete | private method used to remove records from the database using the DELETE statement |
| dbUpdate | private method used to edit records already in the database |
| dbConnect | private method, uses the connectionString and database driver to connect to the database|
| dbDisconnect | private method, closes the connection to the database |
| reportFileDownload | public method used by clients to report a completed download |
| reportFileUpload | public method used by clients to report a completed upload |
| designateFileSponsoredStatus | public method used to update a file record and change it's sponsored status field |
| getFileStatistics | public method used to get a specific file's record from the database |
| invoke | instantiates the DBManager |
| destroy | destroys the DBManager |

### 5.4 Content Manager ###
The Content Manager subsystem is a server-side system which handles requests from zero to many client systems.  It also filters database requests from the client and passes them along to the Database Manager subsystem (this is to keep consistent with the MVC architecture) as well as making its own requests to the database.

The Content Manager's internal associations, as well as remote associations to the database and clients are depicted below:

http://nmt-cs326-g5.googlecode.com/files/ssinteraction_cm_v2.JPG

The Content Manager is implemented via a single class, `ContentManager`, pictured below:

![http://nmt-cs326-g5.googlecode.com/files/Class%20Diagram%20-%20Content%20Manager%20%282%29.jpeg](http://nmt-cs326-g5.googlecode.com/files/Class%20Diagram%20-%20Content%20Manager%20%282%29.jpeg)

The `ContentManager` implements several methods to handle various requests from clients.  The connect() and disconnect() methods handle the connection and handshaking process between server and client, as well as authentication (via the getUserPermissions() method).  The browseContentSite() method retrieves a web page and sends it to the requesting client (who requested it via the Web Browser subsystem).

The getFileLocation() method is used for file transfer requests (as all requests for file transfer to the content server occur over HTTP, this method is blind to the type of file requested apart from basic security considerations).  The setServerPreferences() method is used to set various server and community options (like whether or not basic users are allowed to upload content, creating a toggle between an open and closed file distribution community), and can only be used by Content Distributors, who are authenticated by the methods previously discussed.

Finally, the reportCompletedTransfer() method uses the Database Manager subsystem to report a completed file transfer (via the private reportDownload() and reportUpload() methods) and update the file's statistics (download count, etc).

_Class: `ContentManager`_

Attributes:
| **Name** | **Type** | **Description** |
|:---------|:---------|:----------------|
| location | String | the network location of the content manager |
| transferManager | `TransferManager` | manages the various transfers back and forth; see transfer subsystem |

Methods:
| **Name** | **Description** |
|:---------|:----------------|
| sendFile | initiate a transfer to a client |
| getFileLocation | query the database as to the whereabouts of a specific file |
| authenticateUser | query the database to confirm a user exists |
| getUserPermissions | query the database as to a user's credentials |
| attachToServer | connect to a server |
| detachFromServer | break a connection with a server |
| sendWebPage | deliver web content to a GUI |
| setServerPreferences | allows a user with the correct permissions to change how a server behaves |
| reportCompletedTransfer | let the DBManager know of a completed transfer |
| reportDownload | communicate a completed download to the DBManager |
| reportUpload | communicate a completed upload to the DBManager |
| invoke | instantiate the `ContentManager` |
| destroy | destroy the `ContentManager` instance |


---


## 6. Human Interfaces ##
The following are two screenshots of a sample client, running first in Windows Vista, the second in Macintosh OS X.

Vista:

![http://nmt-cs326-g5.googlecode.com/files/winvista.png](http://nmt-cs326-g5.googlecode.com/files/winvista.png)

OS X:

![http://nmt-cs326-g5.googlecode.com/files/macosx.png](http://nmt-cs326-g5.googlecode.com/files/macosx.png)

The following is a screenshot of a client with the Web Browser subsystem implemented; the client is capable of an in-house web browsing via an internal Firefox implementation.

http://nmt-cs326-g5.googlecode.com/files/Capture.PNG


---


## 7. System/Data Dependencies & Requirements ##

The application requires a server of moderate system requirements to run the Content Manager subsystem.  In addition, the same server may house the (server-side) Database Manager subsystem (as well as the physical database), or the Database Manager may reside on another remote server.

The client application requires a machine with an internet connection, and the Microsoft Windows, Mac OS X, or most flavors of Linux to function.

---


## 8. Testing Plan ##

The system will be deployed in the configuration specified by the deployment diagram, though several variations on operating systems will be used in the client to insure cross-platform compatibility.  The machine used to host the server and database systems will be varied as well during the testing phase.

The testing plan will encompass the use cases, as specified in the Requirements Analysis:

**Download/Upload Use Cases**

These use cases will be tested via a direct examination of each of the respective functionalities.  Multiple file types will be tested as well as different connections for uploading/downloading to measure performance.

**Database Use Cases**

These use cases will be tested individually as well as simultaneously alongside the download/upload use cases (as the database use cases are often invoked as a result of these use cases).  Invalid queries will also be made on the database to ensure that the database constraints are sufficient to maintain the integrity of the system's relational structure.

**Miscellaneous Client/Server Use Cases (Preferences, Browsing, etc.)**

These use cases will be tested via a direct examination of each functionality; for example, changing server preferences will be tested to see if its intended functionality is in place as well as the functionality to refute/correct improper changes in preferences.

**Exceptional Use Cases (Errors)**

These use cases will be tested by forcing each respective error to occur as well as simulating conditions in which each error might be likely to occur.

**Examples of Specific Testing Cases**

  * Successfully complete an HTTP download
  * Successfully complete a torrent download
  * Downloads will be verified using a checksum, thereby verifying that the files downloaded are identical to the files on the server
  * `BasicUser` can successfully change preferences using the proper dialog
  * `ContentServer` can communicate with the `DBManager`, verified by doing database inserts,selects,deletes and edits
  * `DBManager` can successfully communicate with the actual database, verified by doing database inserts, selects, deletes and edits, and verifying the actual data inserted by accessing the database through the command line
  * `ContentServer` can successfully communicate the location and attributes of a specific file download, both in the case of HTTP downloads and the case of torrent downloads


---


## 9. Appendices ##

### 9.1 Project Status ###

The project is on schedule, with the design phase completed and several prototypes already having been implemented. The following is an updated Gantt chart for project progress, reflecting the partial progress made on the implementation phases:

http://nmt-cs326-g5.googlecode.com/files/ganttchart_3.JPG

### 9.2 Database Schema ###

The following is an entity relationship diagram depicting the database:
![http://nmt-cs326-g5.googlecode.com/files/db_er.jpeg](http://nmt-cs326-g5.googlecode.com/files/db_er.jpeg)

| **Table Name** | **Description** |
|:---------------|:----------------|
| downloads | keeps track of specific downloads |
| files | keeps track of files located on the server, and what type of download they are |
| uploads | keeps track of uploads and where they came from |
| users | keeps track of the two different types of users |

#### Fields: ####
Download table:
| **field** | **type** | **description** |
|:----------|:---------|:----------------|
| fid | int | the identification number of the file |
| dateOfDownload | date | when the file was downloaded |
| uid | int | corresponds to the user that downloaded the file |

Files table:
| **field** | **type** | **description** |
|:----------|:---------|:----------------|
| fid | int | the identification number of the file |
| name | string | the name of the file |
| location | string | where the file is on the server, represented by a string |
| type | string | the type of file |
| active | bit | a boolean value that defines whether the file is visible to regular users |
| sponsoredStatus | bit | a boolean value that defines whether the file is sponsored by a Content Distributor |
| downloadCount | int | the number of times a file has been downloaded, corresponding to the number of records in the Download table associated with this files fid |

Uploads table:
| **field** | **type** | **description** |
|:----------|:---------|:----------------|
| dateOfUpload | date | when the file was uploaded |
| fid | int | the id of the file |

Users table:
| **field** | **type** | **description** |
|:----------|:---------|:----------------|
| uid | int | the identification number of the user |
| fname | string | first name |
| lname | string | last name |
| passwd | string | the encrypted password of the user |
| userLevel | int | the permission level of the user |

Database schema:


--
-- Table structure for table `downloads`
--

CREATE TABLE `downloads` (
> `fid` int(11) NOT NULL,
> `dateOfDownload` date default NULL
)

--
-- Table structure for table `files`
--

CREATE TABLE `files` (
> `fid` int(11) NOT NULL,
> `name` varchar(255) default NULL,
> `location` varchar(255) default NULL,
> `type` char(10) default NULL,
> `active` bit(1) default NULL,
> `sponsoredStatus` bit(1) default NULL,
> `downloadCount` int(11) default NULL,
> PRIMARY KEY  (`fid`)
)

--
-- Table structure for table `uploads`
--

CREATE TABLE `uploads` (
> `dateOfUpload` date default NULL,
> `fid` int(11) NOT NULL,
> PRIMARY KEY  (`fid`)
)


--
-- Table structure for table `users`
--

CREATE TABLE `users` (
> `uid` int(11) NOT NULL,
> `fname` char(25) default NULL,
> `lname` char(25) default NULL,
> `passwd` varchar(30) default NULL,
> `userLevel` char(1) default NULL,
> PRIMARY KEY  (`uid`)
)


### 9.3 System Resource Documentation ###

`WxWidgets` -
http://www.wxwidgets.org/

CMake -
http://www.cmake.org/

Bittorrent specifications -
http://wiki.theory.org/BitTorrentSpecification#Identification

BEncoding C implementation -
http://funzix.svn.sourceforge.net/viewvc/funzix/trunk/bencode/bencode.c?view=markup

Libtorrent -
http://www.rasterbar.com/products/libtorrent/

cURL file transfer tool -
http://curl.haxx.se/

Apache HTTP server -
http://www.apache.org/

MySQL Relational Database system -
http://www.mysql.com/