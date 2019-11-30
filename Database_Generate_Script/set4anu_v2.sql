CREATE TABLE "match" (
	"mid" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, 
	"mentor_id" VARCHAR (10) NOT NULL, 
	"mentee_id" VARCHAR (10) NOT NULL
	);

CREATE TABLE "mentee" (
	"uid" VARCHAR (10) PRIMARY KEY NOT NULL UNIQUE, 
	"first_name" VARCHAR (20) NOT NULL, 
	"last_name" VARCHAR (20) NOT NULL, 
	"academic_level" VARCHAR (20) NOT NULL, 
	"college" VARCHAR (50) NOT NULL, 
	"requests" TEXT (500), 
	"round_1" CHAR (1) NOT NULL, 
	"round_2" CHAR (1) NOT NULL
	);

CREATE TABLE "mentor" (
	"uid" VARCHAR (10) PRIMARY KEY NOT NULL UNIQUE, 
	"first_name" VARCHAR (20) NOT NULL, 
	"last_name" VARCHAR (20) NOT NULL, 
	"gender" VARCHAR (20) NOT NULL, 
	"academic_level" VARCHAR (20) NOT NULL, 
	"college" VARCHAR (50) NOT NULL, 
	"degree" VARCHAR (30) NOT NULL, 
	"type" VARCHAR (20) NOT NULL, 
	"languages" VARCHAR (20) NOT NULL, 
	"hall" VARCHAR (20) NOT NULL, 
	"special" TEXT (500), 
	"interests" TEXT (500), 
	"wwvp" VARCHAR (10) NOT NULL, 
	"train_1" CHAR (1) NOT NULL, 
	"train_2" CHAR (1) NOT NULL, 
	"train_3" CHAR (1) NOT NULL, 
	"train_complete" CHAR (1) NOT NULL, 
	"round_1" CHAR (1) NOT NULL, 
	"round_2" CHAR (1) NOT NULL
	);
