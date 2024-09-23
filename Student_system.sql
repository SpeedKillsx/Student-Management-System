--
-- Fichier généré par SQLiteStudio v3.4.4 sur dim. sept. 22 19:09:55 2024
--
-- Encodage texte utilisé : System
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Tableau : Student
CREATE TABLE IF NOT EXISTS Student (student_number INTEGER PRIMARY KEY AUTOINCREMENT, name_student TEXT NOT NULL, student_surname TEXT NOT NULL, date_birth TEXT, place_birth TEXT NOT NULL);

COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
