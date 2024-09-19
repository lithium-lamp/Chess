CREATE TABLE IF NOT EXISTS chess_game (
    id serial PRIMARY KEY,
    all_games_id integer REFERENCES all_chess_games(id) NOT NULL,
    move_time timestamp(0) with time zone NOT NULL DEFAULT NOW(),
    fen text NOT NULL,
    version integer NOT NULL DEFAULT 1
);