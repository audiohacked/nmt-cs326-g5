# Class Diagram #
# Version Two #
With the methods implied by the use case diagram. Stuff with (-) in front of it is private, stuff with (+) is public. Made all the actual DB stuff private to enforce encapsulation.
![http://nmt-cs326-g5.googlecode.com/files/class%20diagramV2.jpeg](http://nmt-cs326-g5.googlecode.com/files/class%20diagramV2.jpeg)
# Version One #
I'm gonna match this to the updated use case diagram, of course. Criticisms, ideas, etc. welcome!
![http://nmt-cs326-g5.googlecode.com/files/class%20diagram.jpeg](http://nmt-cs326-g5.googlecode.com/files/class%20diagram.jpeg)

# Classes #

Below is a table of potential classes w/ attributes and methods.

| _Class_ | _Description_ | _Attributes_ | _Methods_ |
|:--------|:--------------|:-------------|:----------|
| GUI | Graphical user interface which wraps wxWidgets methods. | ?? | ?? |
| DBManager | Handles connections/transactions with the database. | connectionString, databaseType | connectToDB(), disconnect(), select(...), insert(...), update(...), remove(...) |
| ContentManager | Handles connections/transactions/authentications with the centralized content server. | location | getFileLocation(), authenticateUser(), getUserPermissions(), connect() |
| TransferManager | Super class for transfer protocols. | file(s), transferSpeeds, etc. | downloadFile(location), getTransferSpeed(file), getPercentCompleted(file) |
| HTTPTransferManager | Manager for HTTP file transfers. | inherited | downloadFile(location), rest are inherited |
| TorrentTransferManager | Manager for torrent file transfers. | trackerLocation, peerLocation(s) | downloadTorrent(torrent), connectToTracker() |
| File | Superclass for files. | name, extension, ?? | ?? |
| TorrentFile | Subclass for torrent file (maybe not necessary) | ?? | ?? |


# Classes and Relationships #

Below is a table textually describing relationships between classes.

| _Class_ | _Related Class_ | _Relationship Type_ | _Cardinalities_ | _Additional Info_  |
|:--------|:----------------|:--------------------|:----------------|:-------------------|
| TransferManager | HTTPTransferManager, TorrentTransferManager | Inheritance | 1:1 | N/A |