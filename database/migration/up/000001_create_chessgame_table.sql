CREATE TABLE IF NOT EXISTS chess_game (
    id serial PRIMARY KEY,
    move_time timestamp(0) with time zone NOT NULL DEFAULT NOW(),
    fen text NOT NULL,
    version integer NOT NULL DEFAULT 1
);