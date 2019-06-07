set schema 'fn45244';

CREATE TYPE BackTypeEnum AS ENUM ('Paperback','Hardcover');

/* Create tables */
create table Person (
PersonalNo CHAR(10) NOT NULL,
Name VARCHAR(255),
Salary INT,
SuperiorPersonalNo CHAR(11),
Position VARCHAR(255),
DepNo INT
);

create table Registered (
PersonalNo CHAR(10) NOT NULL,
ReaderID INT NOT NULL
);

create table Reader (
ReaderID INT NOT NULL,
RegistrationDate DATE,
ExpirationDate DATE
);

create table Fines (
FineNo INT NOT NULL,
PaymentCost INT,
PaymentDate DATE,
ReaderID INT
);

create table WrittenBy (
PersonalNo CHAR(10) NOT NULL,
ISBN VARCHAR(13) NOT NULL
);

create table Department (
DepNo INT NOT NULL,
Name CHAR(30),
Address VARCHAR(255)
);

create table Location (
DepNo INT NOT NULL,
SystemNo VARCHAR(255) NOT NULL
);

create table Inventory (
SystemNo VARCHAR(255) NOT NULL,
ISBN VARCHAR(13),
Taken BOOLEAN
);

create table Borrows (
ReaderID INT NOT NULL,
SystemNo VARCHAR(255) NOT NULL,
BorrowDate DATE NOT NULL,
DueDate DATE,
ReturnDate DATE
);

create table Book (
ISBN VARCHAR(13) NOT NULL,
Title VARCHAR(255),
Pages SMALLINT,
Edition SMALLINT,
BackType BackTypeEnum,
PublisherID INT ,
PublishDate DATE
);

create table Publisher (
PublisherID SERIAL NOT NULL,
Name VARCHAR(255),
Address VARCHAR(255)
);

/* Create constraints */

alter table Person add constraint PK_Person PRIMARY KEY (PersonalNo);
alter table Registered add constraint PK_Registered PRIMARY KEY (PersonalNo,ReaderID);
alter table Reader add constraint PK_Reader PRIMARY KEY (ReaderID);
alter table Fines add constraint PK_Fines PRIMARY KEY (FineNo);
alter table WrittenBy add constraint PK_WrittenBy PRIMARY KEY (PersonalNo,ISBN);
alter table Department add constraint PK_Department PRIMARY KEY (DepNo);
alter table Location add constraint PK_Location PRIMARY KEY (DepNo,SystemNo);
alter table Inventory add constraint PK_Inventory PRIMARY KEY (SystemNo);
alter table Borrows add constraint PK_Borrows PRIMARY KEY (ReaderID,SystemNo,BorrowDate);
alter table Book add constraint PK_Book PRIMARY KEY (ISBN);
alter table Publisher add constraint PK_Publisher PRIMARY KEY (PublisherID);

alter table Book add constraint FK_Book_Publisher FOREIGN KEY (PublisherID) references Publisher (PublisherID) on delete cascade;
alter table Inventory add constraint FK_Inventory_Book FOREIGN KEY (ISBN) references Book (ISBN);
alter table Fines add constraint FK_Fines_Reader FOREIGN KEY (ReaderID) references Reader (ReaderID);
alter table Registered add constraint FK_Registered_Reader FOREIGN KEY (ReaderID) references Reader (ReaderID) on delete cascade;
alter table Registered add constraint FK_Registered_Person FOREIGN KEY (PersonalNo) references Person (PersonalNo);
alter table Person add constraint FK_Person_Department FOREIGN KEY (DepNo) references Department (DepNo);
alter table Location add constraint FK_Location_Department FOREIGN KEY (DepNo) references Department (DepNo);
alter table Location add constraint FK_Location_Inventory FOREIGN KEY (SystemNo) references Inventory (SystemNo);
alter table Borrows add constraint FK_Borrows_Reader FOREIGN KEY (ReaderID) references Reader (ReaderID);
alter table Borrows add constraint FK_Borrows_Inventory FOREIGN KEY(SystemNo) references Inventory (SystemNo);

SET CONSTRAINTS ALL DEFERRED;