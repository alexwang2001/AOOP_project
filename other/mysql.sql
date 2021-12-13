CREATE DATABASE IF NOT EXISTS trainsystem;
USE trainsystem;
CREATE TABLE IF NOT EXISTS account (
    Account VARCHAR(20),
    Password VARCHAR(20),
	Identity VARCHAR(10)
);
CREATE TABLE IF NOT EXISTS stationtable (
    StationName VARCHAR(30),
    StationNO VARCHAR(10)
);
CREATE TABLE IF NOT EXISTS traintable (
    TrainNumber INT(11),
    Departure VARCHAR(20),
    Terminal VARCHAR(20),
    DepartureTime INT(11),
    ArrivalTime INT(11),
    Direction VARCHAR(10),
    mon TINYINT(1),
    tue TINYINT(1),
    wed TINYINT(1),
    thu TINYINT(1),
    fri TINYINT(1),
    sat TINYINT(1),
    sun TINYINT(1)
);
INSERT INTO traintable VALUES (1001,'Alpha','Beta',1120,1240,'north',1,1,1,1,1,0,0);
INSERT INTO traintable VALUES (1002,'Alpha','Beta',1130,1250,'north',1,1,1,1,1,0,0);
INSERT INTO traintable VALUES (1003,'Alpha','Beta',1140,1300,'north',1,1,1,1,1,1,1);
INSERT INTO traintable VALUES (1004,'Beta','Alpha',1430,1600,'north',1,1,1,1,1,1,1);
INSERT INTO traintable VALUES (1005,'Beta','Alpha',1140,1300,'north',1,1,1,1,1,1,1);
INSERT INTO traintable VALUES (1006,'Alpha','Beta',1140,1300,'north',1,1,1,1,1,1,1);
INSERT INTO traintable VALUES (1007,'Alpha','Beta',1140,1300,'north',1,1,1,1,1,1,1);
INSERT INTO traintable VALUES (1008,'Alpha','Beta',1140,1300,'north',1,1,1,1,1,1,1);
INSERT INTO traintable VALUES (1009,'Alpha','Beta',1140,1300,'north',1,1,1,1,1,1,1);
INSERT INTO stationtable VALUES ('Alpha',0);
INSERT INTO stationtable VALUES ('Beta',1);
INSERT INTO stationtable VALUES ('Gamma',2);
INSERT INTO account VALUES ('alexwang','123456','Client');

SELECT * FROM stationtable;
SELECT * FROM traintable;
SELECT * FROM account;

CREATE DATABASE IF NOT EXISTS request;
USE request;
CREATE TABLE IF NOT EXISTS requestqueue (
	url VARCHAR(100)
);

CREATE DATABASE IF NOT EXISTS response;
USE response;

CREATE USER 'initial'@'%' IDENTIFIED BY 'tsaimotheriloveyou';
GRANT INSERT ON request.* TO 'initial'@'%';
flush privileges;
USE response;
CREATE TABLE IF NOT EXISTS new (
	IP VARCHAR(15),
    response INT(4)
);
GRANT SELECT ON response.new TO 'initial'@'%';
flush privileges;

SHOW GLOBAL VARIABLES LIKE 'PORT';