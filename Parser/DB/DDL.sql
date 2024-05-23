/*
Created: 19/05/2024
Modified: 19/05/2024
Model: chart_sqlite
Database: SQLite 3.7
*/


-- Create tables section -------------------------------------------------

-- Table series

CREATE TABLE series
(
    id INTEGER NOT NULL
        CONSTRAINT PK_series PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL
);

CREATE UNIQUE INDEX IX_series_name ON series (name);

-- Table game

CREATE TABLE game
(
    id INTEGER NOT NULL
        CONSTRAINT PK_game PRIMARY KEY AUTOINCREMENT,
    series_id INTEGER NOT NULL,
    name TEXT NOT NULL,
    version INTEGER NOT NULL,
    CONSTRAINT game_series FOREIGN KEY (series_id) REFERENCES series (id) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE INDEX IX_game_series ON game (series_id);

-- Table game_release

CREATE TABLE game_release
(
    id INTEGER NOT NULL
        CONSTRAINT PK_game_release PRIMARY KEY AUTOINCREMENT,
    game_id INTEGER NOT NULL,
    code TEXT NOT NULL,
    CONSTRAINT game_release_game FOREIGN KEY (game_id) REFERENCES game (id) ON DELETE RESTRICT ON UPDATE RESTRICT
);

CREATE INDEX IX_game_release_game ON game_release (game_id);

-- Table sdvx_song

CREATE TABLE sdvx_song
(
    id INTEGER NOT NULL
        CONSTRAINT PK_sdvx_song PRIMARY KEY AUTOINCREMENT,
    title TEXT NOT NULL,
    artist TEXT NOT NULL,
    infinite_version INTEGER
);

-- Table sdvx_chart

CREATE TABLE sdvx_chart
(
    id INTEGER NOT NULL
        CONSTRAINT PK_sdvx_chart PRIMARY KEY AUTOINCREMENT,
    sdvx_song_id INTEGER NOT NULL,
    max_ex_score INTEGER,
    CONSTRAINT sdvx_chart_sdvx_song FOREIGN KEY (sdvx_song_id) REFERENCES sdvx_song (id) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE INDEX IX_sdvx_chart_sdvx_song ON sdvx_chart (sdvx_song_id);

-- Table sdvx_song_entry

CREATE TABLE sdvx_song_entry
(
    id INTEGER NOT NULL
        CONSTRAINT PK_sdvx_song_entry PRIMARY KEY AUTOINCREMENT,
    game_release_id INTEGER NOT NULL,
    sdvx_song_id INTEGER NOT NULL,
    internal_id INTEGER NOT NULL,
    CONSTRAINT sdvx_song_entry_sdvx_song FOREIGN KEY (sdvx_song_id) REFERENCES sdvx_song (id) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT sdvx_song_entry_game_release FOREIGN KEY (game_release_id) REFERENCES game_release (id) ON DELETE RESTRICT ON UPDATE RESTRICT
);

CREATE INDEX IX_sdvx_song_entry_sdvx_song ON sdvx_song_entry (sdvx_song_id);

CREATE INDEX IX_sdvx_song_entry_game_release ON sdvx_song_entry (game_release_id);

-- Table sdvx_chart_entry

CREATE TABLE sdvx_chart_entry
(
    id INTEGER NOT NULL
        CONSTRAINT PK_sdvx_chart_entry PRIMARY KEY AUTOINCREMENT,
    sdvx_chart_id INTEGER NOT NULL,
    sdvx_song_entry_id INTEGER NOT NULL,
    difficulty INTEGER NOT NULL,
    level INTEGER NOT NULL,
    limited INTEGER NOT NULL,
    CONSTRAINT sdvx_chart_entry_sdvx_chart FOREIGN KEY (sdvx_chart_id) REFERENCES sdvx_chart (id) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT sdvx_chart_entry_sdvx_song_entry FOREIGN KEY (sdvx_song_entry_id) REFERENCES sdvx_song_entry (id) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE INDEX IX_sdvx_chart_entry_sdvx_chart ON sdvx_chart_entry (sdvx_chart_id);

CREATE INDEX IX_sdvx_chart_entry_sdvx_song_entry ON sdvx_chart_entry (sdvx_song_entry_id);

