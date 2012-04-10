PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE user (id integer not null primary key autoincrement,username varchar not null,passwd varchar not null);
INSERT INTO "user" VALUES(1,'user1','123456');
INSERT INTO "user" VALUES(2,'user2','123456');
INSERT INTO "user" VALUES(3,'','');
INSERT INTO "user" VALUES(4,'user4','111111');
INSERT INTO "user" VALUES(5,'user5','123456');
CREATE TABLE ticket(
id integer not null primary key autoincrement,
from_station varchar not null,
to_station varchar not null,
price integer not null,
days_left integer not null);
INSERT INTO "ticket" VALUES(1,'station1','station2',1,1);
INSERT INTO "ticket" VALUES(2,'station2','station3',2,3);
INSERT INTO "ticket" VALUES(3,'station2','station4',2,7);
INSERT INTO "ticket" VALUES(4,'station5','station4',100,7);
INSERT INTO "ticket" VALUES(5,'station6','station1',22,4);
INSERT INTO "ticket" VALUES(6,'station6','station2',12,5);
CREATE TABLE ticket_order(id integer not null primary key autoincrement,user_id integer not null,ticket_id integer not null,date datetime not null,foreign key(user_id) references "user"(id),foreign key(ticket_id) references "ticket"(id));
INSERT INTO "ticket_order" VALUES(1,1,1,'2012-03-17 21:44:28');
INSERT INTO "ticket_order" VALUES(2,1,2,'2012-03-17 21:45:13');
INSERT INTO "ticket_order" VALUES(3,4,2,'2012-03-17 22:00:00');
INSERT INTO "ticket_order" VALUES(4,1,4,'2012-03-17 22:09:44');
INSERT INTO "ticket_order" VALUES(5,5,3,'2012-04-04 16:44:03');
INSERT INTO "ticket_order" VALUES(6,5,1,'2012-04-04 17:33:50');
DELETE FROM sqlite_sequence;
INSERT INTO "sqlite_sequence" VALUES('user',5);
INSERT INTO "sqlite_sequence" VALUES('ticket',6);
INSERT INTO "sqlite_sequence" VALUES('ticket_order',6);
COMMIT;
