# Digital Content Distribution and Publishing System #
# Team #5 #
## Requirements Specification ##

### Project Overview ###
The program will provide a cross-platform content distribution and publishing service. It will use a client-server model where the server will use and provide service through standard programs/services like Apache and MySQL. The customer can choose to use the server to distribute published files or allow users to upload their own content that can be sponsored/featured on the server.

The motivation for this project is the lack of a general-purpose, platform-independent content distribution service in the market.  Many content distribution services, such as Valve's Steam platform for game distribution, Apple's iTunes service for music distribution, or Netflix's online movie watching software, have some form of platform-dependency (whether it be a an operating system or browser) and/or are content-specific; this is to say that they allow the distribution of only certain forms of digital content.

### Scope and Objectives ###
The scope of the project is to build a base platform for customers to create a digital community and publishing system while also supporting at least Linux, Windows, and Mac user alike. The main function of the system is to provide an end-user a way to obtain any digital content, such as movies, music, and other entertainment. The system has to be fast, native-looking, and easily changeable/upgradeable. To insure the user's client is up to date, it will include an self updater. To facilitate downloading, the client will use bittorrent and http/ftp. Finally, the client can also be configured to include Community Portal and/or a web browser.

### Supplementary Requirements ###
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

**FURPS+ Additional Non-functional Requirements (Constraints)**

_Implementation_
  * The client will be implemented in C++, utilizing the gtkWidgets library for cross-platform code.

### Customer Requirements ###

**Use-Case Diagram - Entire System**

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


**Deployment Diagram**

![http://nmt-cs326-g5.googlecode.com/files/DeploymentDiagram.jpeg](http://nmt-cs326-g5.googlecode.com/files/DeploymentDiagram.jpeg)

## Requirements Analysis ##
### Structural Analysis ###

![http://nmt-cs326-g5.googlecode.com/files/class%20diagramV2.jpeg](http://nmt-cs326-g5.googlecode.com/files/class%20diagramV2.jpeg)

_Boundary_
  * `GUI` - Provides the user interface, the main interaction between the user and the program. Used to initiate downloads, uploads, browse the content server, and edit user preferences.  Calls the preferenceDialogue when preferences are changed and communicates with the ContentManager class to initiate downloads/uploads.
  * `preferenceDialogue` - allows the user to edit their preferences relating to the operation of the program, including options related to torrenting and user interface options.

_Control_
  * `ContentManager` - is the controller that provides the client with all information pertaining to downloads available, browsing the downloads available, user authentication, and uploading of files. Communicates directly with the database server through the DBManager class.
  * `TransferManager` - provides the interface that the other transfer managers implement
  * `TorrentTransferManager` - implements methods included in TransferManager and methods specific to torrent downloads, such as connectToTracker()
  * `HTTPTransferManager` - implements methods included in TransferManager and methods specific to HTTP transfers

_Entity_
  * `DBManager` - provides an interface to the ContentManager to update and query the database, which provides lists and attributes of downloads and the files that make up the downloads.
  * `Download` - provides an interface that specific downloads implement that includes methods and attributes that are common to all downloads.
  * `TorrentDownload` - implements the Download interface and includes methods and attributes that are unique to torrent downloading, such as peerLocations and trackerLocations. Includes one or more file objects.
  * `HTTPDownload` - implements the Download interface and includes methods and attributes that are unique to HTTP downloads, such as getFileName. Includes one file.
  * `file` - includes attributes of a file and a method for retrieving those attributes.

### Behavioral Analysis ###

The following is a table describing the use cases; below the table are sequence or activity diagrams detailing the use cases' flow of events.

| _Use Case_ | _Actor(s)_ | _Entry Condition_ | _Exit Condition_  | _Extends/Includes/Inherits_ |
|:-----------|:-----------|:------------------|:------------------|:----------------------------|
| **`DownloadFile`** | `BasicUser` | `BasicUser` initiates a file download from the `ContentServer` (can be an actual file or a torrent file). | `BasicUser` finishes file download or file download error. | **Includes** **`ReportTransferProgress`**, **`ReportFileDownload`** |
| **`DownloadHTTPFile`** | `BasicUser`, `ContentServer` | `BasicUser` downloads a file from content server over HTTP. | File transfer completes or file transfer error. | **Inherits** **`DownloadFile`** |
| **`DownloadTorrentFile`** | `BasicUser`, `Tracker` | `BasicUser` initiates a file download via BitTorrent. | `BasicUser` completes download and shares file to a specified ratio, or user opts to stop sharing or downloading the file prematurely. | **Inherits** **`DownloadFile`** |
| **`ReportFileDownload`** | `DBManager` | A file transfer to the client completes. | File download statistics are reported and stored in the database. | N/A |
| **`ReportFileUpload`** | `DBManager` | File finishes uploading to the `ContentServer`. | The database has allocated the proper space and structure to accommodate statistics for the sponsored file. | N/A |
| **`UploadFile`** | `BasicUser`, `ContentServer`  | `BasicUser` selects a file which will become sponsored content. | File is uploaded to `ContentServer`. | **Includes** **`ReportFileUpload`**, **`ReportTransferProgress`**, **`DesignateFileSponsoredStatus`** |
| **`DesignateFileSponsoredStatus`** | `ContentDistributor`, `DBManager` | `ContentDistributor` designates a file which he/she wants to have/lose sponsored status. | File's database entry is updated to reflect desired sponsored status. | N/A |
| **`GetFileStatistics`** | `BasicUser`, `DBManager` | `BasicUser` selects a file for which usage statistics are desired. | Database completes reporting relevant information about desired file to client. | N/A |
| **`ReportTransferProgress`** | `BasicUser` | `BasicUser` begins a file transfer. | File transfer completes. | N/A |
| **`BrowseContentSite`** | `BasicUser`, `ContentServer` | `BasicUser` requests a page/navigates in the `ContentServer`'s website. | `ContentServer` serves the client the desired page. | N/A |
| **`RemoveFile`** | `BasicUser`, `ContentServer`, `DBManager` | `BasicUser`/`ContentDistributor` selects a file to be removed from the distribution system. | The server has deleted the file, the database has removed/archived information about the file. | N/A |
| **`SetClientPreferences`** | `BasicUser` | `BasicUser` opens Preferences dialog. | `BasicUser`'s preferences are committed to a configuration file. | N/A |
| **`SetServerPreferences`** | `ContentDistributor`, `ContentServer` | `BasicUser` opens Server Preferences dialog (could be in website with credentials). | New preferences are committed to server configuration file. | N/A |
| **`AbortFileTransfer`** | `BasicUser` | `BasicUser` opts to cancel a file transfer or an error occurs. | File transfer is stopped and any intermediate data is disposed of. | N/A |
| **`ExTransferError`** | `BasicUser` _and/or_ `ContentServer` | Error occurs during a file transfer. | Error is resolved and/or reported to the user. | **Includes** **`AbortFileTransfer`**, **Extends** **`DownloadFile`**, **`UploadFile`** |
| **`ExFileNotFoundError`** | `ContentServer` | `ContentServer` cannot locate requested file. | Server logs the error and aborts the transfer. | **Inherits** ExTransferError |
| **`ExHTTPTransferError`** | `BasicUser` _and/or_ `ContentServer` | An error occurs during an HTTP file transfer. | Error is resolved and/or reported to the user.  If the file was a sponsored file, error is reported to the content server. | **Inherits** **`ExTransferError`**, **Extends** **`DownloadHTTPFile`** |
| **`ExTorrentTransferError`** | `BasicUser`, `Tracker` | An error occurs during a BitTorrent file transfer.  | Error is resolved and/or reported to the user and the tracker. | **Inherits** **`ExTransferError`**, **Extends** **`DownloadTorrentFile`** |


---


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

**Sequence Diagram**

![http://nmt-cs326-g5.googlecode.com/files/seq_abstractdownload.jpeg](http://nmt-cs326-g5.googlecode.com/files/seq_abstractdownload.jpeg)


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

**Sequence Diagram**

![http://nmt-cs326-g5.googlecode.com/files/seq_reportfiledownload.jpeg](http://nmt-cs326-g5.googlecode.com/files/seq_reportfiledownload.jpeg)


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

**Sequence Diagram**

![http://nmt-cs326-g5.googlecode.com/files/seq_reportfileupload.jpeg](http://nmt-cs326-g5.googlecode.com/files/seq_reportfileupload.jpeg)


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

**Activity Diagram**

![http://nmt-cs326-g5.googlecode.com/files/act_upload.jpeg](http://nmt-cs326-g5.googlecode.com/files/act_upload.jpeg)


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

**Activity Diagram**

See the authentication/designation section of the **`UploadFile`** activity diagram.


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

**Sequence Diagram**

http://nmt-cs326-g5.googlecode.com/files/seq_reporttransferprogress2.JPG


---


_Use case name_  **`BrowseContentSite`**

_Participating Actors_

> Initiated by `Basic User`

> Communicates with `ContentServer`

**Flow of Events**

  1. `BasicUser` requests a page via the in-house browser from the `ContentServer`.

> 2. `ContentServer` receives request and serves page to client.

> 3. `Client` renders page in browser.

**Sequence Diagram**

![http://nmt-cs326-g5.googlecode.com/files/seq_browsecontent.jpeg](http://nmt-cs326-g5.googlecode.com/files/seq_browsecontent.jpeg)


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

**Activity Diagram**

![http://nmt-cs326-g5.googlecode.com/files/act_removefile.jpeg](http://nmt-cs326-g5.googlecode.com/files/act_removefile.jpeg)


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

**Sequence Diagram**

![http://nmt-cs326-g5.googlecode.com/files/seq_setclientpreferences.jpeg](http://nmt-cs326-g5.googlecode.com/files/seq_setclientpreferences.jpeg)


---


_Use case name_  **`SetServerPreferences`**

_Participating Actors:_

Initiated by `ContentDistributor`

Communicates with `ContentServer`

_Flow of Events_

  1. `ContentDistributor` edits server preferences via configuration file.
  1. `ContentServer` reads and implements changed preferences.

**Sequence Diagram**

![http://nmt-cs326-g5.googlecode.com/files/seq_setserverpreferences.jpeg](http://nmt-cs326-g5.googlecode.com/files/seq_setserverpreferences.jpeg)


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

**Activity Diagram**

![http://nmt-cs326-g5.googlecode.com/files/act_aborttransfer.jpeg](http://nmt-cs326-g5.googlecode.com/files/act_aborttransfer.jpeg)


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

**Activity Diagram**

![http://nmt-cs326-g5.googlecode.com/files/act_exception.jpeg](http://nmt-cs326-g5.googlecode.com/files/act_exception.jpeg)


---

_Use case name_ **`ExFileNotFoundError`**

_Participating Actors:_ `ContentServer`, `BasicUser`

_Flow of events_

  1. `ContentServer` reports error.

> 2.   Error reported to `BasicUser`.

_Entry conditions_

  * `BasicUser` has requested a file that the server could not locate

**Activity Diagram**

See activity diagram for **`ExTransferError`**.


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

**Activity Diagram**

See activity diagram for **`ExTransferError`**.


---


### User Interface Analysis ###
The essential design of the user interface is a tabbed client which allows the user to switch from viewing features like a Content Browser (in-house web browser for the content server's website), a Community Portal (allowing users to manage content), or a Transfer tab (detailing current downloads/uploads).  Drop-down menus are also provided which support an 'expected' set of functionality on each OS, such as closing the client or setting preferences.

The following are two screenshots of a sample client, running first in Windows Vista, the second in Macintosh OS X.

![http://nmt-cs326-g5.googlecode.com/files/winvista.png](http://nmt-cs326-g5.googlecode.com/files/winvista.png)

![http://nmt-cs326-g5.googlecode.com/files/macosx.png](http://nmt-cs326-g5.googlecode.com/files/macosx.png)

### Validation and Criteria ###
The following are validation and testing criterion for each category of use cases.  In addition to the testing strategies described, all categories have an addition of testing the use case across all targeted operating systems.

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
  * `BasicUser` can successfully change preferences using the proper dialogue
  * `ContentServer` can communicate with the `DBManager`, verified by doing database inserts,selects,deletes and edits
  * `DBManager` can successfully communicate with the actual database, verified by doing database inserts, selects, deletes and edits, and verifying the actual data inserted by accessing the database through the command line
  * `ContentServer` can successfully communicate the location and attributes of a specific file download, both in the case of HTTP downloads and the case of torrent downloads

## Project Status ##
The project is on schedule with the requirements elicitation and analysis phases completed.  Via mockups and experimentation, some of the design and implementation is complete as well.

Below is an updated Gantt chart showing project progress thus far:

http://nmt-cs326-g5.googlecode.com/files/ganttchart_2.JPG

## Appendices ##
System Resource Documentation:

WxWidgets -
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