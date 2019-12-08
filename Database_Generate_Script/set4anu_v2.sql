BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS [mentor] (
	uid	VARCHAR(10) NOT NULL UNIQUE,
	first_name	VARCHAR(20) NOT NULL,
	last_name	VARCHAR(20) NOT NULL,
	gender	VARCHAR(20) NOT NULL,
	academic_level	VARCHAR(20) NOT NULL,
	college	VARCHAR(50) NOT NULL,
	degree	VARCHAR(100) NOT NULL,
	type	VARCHAR(50) NOT NULL,
	languages	VARCHAR(20) NOT NULL,
	languages_text	TEXT(500),
	hall	VARCHAR(20) NOT NULL,
	special	TEXT(1000),
	interests	TEXT(1000),
	wwvp	VARCHAR(10) NOT NULL,
	train_1	CHAR(1) NOT NULL DEFAULT 'n',
	train_2	CHAR(1) NOT NULL DEFAULT 'n',
	train_3	CHAR(1) NOT NULL DEFAULT 'n',
	train_complete	CHAR(1) NOT NULL,
	round	TEXT(100),
	group_id	INTEGER NOT NULL DEFAULT 0,
	is_confirmed TEXT(500),
	PRIMARY KEY("uid")
);
CREATE TABLE IF NOT EXISTS [mentee] (
	uid	VARCHAR(10) NOT NULL UNIQUE,
	first_name	VARCHAR(20) NOT NULL,
	last_name	VARCHAR(20) NOT NULL,
	gender	VARCHAR(20) NOT NULL,
	academic_level	VARCHAR(20) NOT NULL,
	college	VARCHAR(50) NOT NULL,
	degree	VARCHAR(100) NOT NULL,
	type	VARCHAR(50) NOT NULL,
	languages	VARCHAR(20) NOT NULL,
	languages_text	TEXT(500),
	requests	TEXT(1000),
	special_categories	TEXT(1000),
	round	TEXT(100),
	group_id	INTEGER NOT NULL DEFAULT 0,
	PRIMARY KEY("uid")
);
COMMIT;
