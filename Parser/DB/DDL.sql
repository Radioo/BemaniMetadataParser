/*
Created: 30/04/2024
Modified: 03/05/2024
Model: chart
Database: MySQL 8.0
*/

-- Create tables section -------------------------------------------------

-- Table series

CREATE TABLE `series`
(
    `id` Int UNSIGNED NOT NULL AUTO_INCREMENT,
    `name` Varchar(255) NOT NULL,
    PRIMARY KEY (`id`)
)
;

-- Table game

CREATE TABLE `game`
(
    `id` Int UNSIGNED NOT NULL AUTO_INCREMENT,
    `series_id` Int UNSIGNED NOT NULL,
    `name` Varchar(255) NOT NULL,
    `version` Tinyint UNSIGNED NOT NULL,
    PRIMARY KEY (`id`)
)
;

CREATE INDEX `IX_game_series` ON `game` (`series_id`)
;

-- Table game_release

CREATE TABLE `game_release`
(
    `id` Int UNSIGNED NOT NULL AUTO_INCREMENT,
    `game_id` Int UNSIGNED NOT NULL,
    `code` Varchar(255) NOT NULL,
    PRIMARY KEY (`id`)
)
;

CREATE INDEX `IX_game_release_game` ON `game_release` (`game_id`)
;

-- Table sdvx_song

CREATE TABLE `sdvx_song`
(
    `id` Int UNSIGNED NOT NULL AUTO_INCREMENT,
    `title` Varchar(255) NOT NULL,
    `artist` Varchar(255) NOT NULL,
    `infinite_version` Tinyint UNSIGNED,
    PRIMARY KEY (`id`)
)
;

-- Table sdvx_chart

CREATE TABLE `sdvx_chart`
(
    `id` Int UNSIGNED NOT NULL AUTO_INCREMENT,
    `sdvx_song_id` Int UNSIGNED NOT NULL,
    `max_ex_score` Int UNSIGNED,
    PRIMARY KEY (`id`)
)
;

CREATE INDEX `IX_sdvx_chart_sdvx_song` ON `sdvx_chart` (`sdvx_song_id`)
;

-- Table sdvx_song_entry

CREATE TABLE `sdvx_song_entry`
(
    `id` Int UNSIGNED NOT NULL AUTO_INCREMENT,
    `game_release_id` Int UNSIGNED NOT NULL,
    `sdvx_song_id` Int UNSIGNED NOT NULL,
    `internal_id` Int UNSIGNED NOT NULL,
    PRIMARY KEY (`id`)
)
;

CREATE INDEX `IX_sdvx_song_entry_sdvx_song` ON `sdvx_song_entry` (`sdvx_song_id`)
;

CREATE INDEX `IX_sdvx_song_entry_game_release` ON `sdvx_song_entry` (`game_release_id`)
;

-- Table sdvx_chart_entry

CREATE TABLE `sdvx_chart_entry`
(
    `id` Int UNSIGNED NOT NULL AUTO_INCREMENT,
    `sdvx_chart_id` Int UNSIGNED NOT NULL,
    `sdvx_song_entry_id` Int UNSIGNED NOT NULL,
    `difficulty` Tinyint UNSIGNED NOT NULL,
    `level` Tinyint UNSIGNED NOT NULL,
    `limited` Tinyint UNSIGNED NOT NULL,
    PRIMARY KEY (`id`)
)
;

CREATE INDEX `IX_sdvx_chart_entry_sdvx_chart` ON `sdvx_chart_entry` (`sdvx_chart_id`)
;

CREATE INDEX `IX_sdvx_chart_entry_sdvx_song_entry` ON `sdvx_chart_entry` (`sdvx_song_entry_id`)
;

-- Create foreign keys (relationships) section -------------------------------------------------

ALTER TABLE `game` ADD CONSTRAINT `game_series` FOREIGN KEY (`series_id`) REFERENCES `series` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
;

ALTER TABLE `game_release` ADD CONSTRAINT `game_release_game` FOREIGN KEY (`game_id`) REFERENCES `game` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT
;

ALTER TABLE `sdvx_chart` ADD CONSTRAINT `sdvx_chart_sdvx_song` FOREIGN KEY (`sdvx_song_id`) REFERENCES `sdvx_song` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
;

ALTER TABLE `sdvx_song_entry` ADD CONSTRAINT `sdvx_song_entry_sdvx_song` FOREIGN KEY (`sdvx_song_id`) REFERENCES `sdvx_song` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
;

ALTER TABLE `sdvx_song_entry` ADD CONSTRAINT `sdvx_song_entry_game_release` FOREIGN KEY (`game_release_id`) REFERENCES `game_release` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT
;

ALTER TABLE `sdvx_chart_entry` ADD CONSTRAINT `sdvx_chart_entry_sdvx_chart` FOREIGN KEY (`sdvx_chart_id`) REFERENCES `sdvx_chart` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
;

ALTER TABLE `sdvx_chart_entry` ADD CONSTRAINT `sdvx_chart_entry_sdvx_song_entry` FOREIGN KEY (`sdvx_song_entry_id`) REFERENCES `sdvx_song_entry` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
;

