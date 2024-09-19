CREATE TABLE IF NOT EXISTS all_chess_games (
    id serial PRIMARY KEY,
    user_id1 integer REFERENCES users(id) NOT NULL,
    user_id2 integer REFERENCES users(id) NOT NULL,
    created_at timestamp(0) with time zone NOT NULL DEFAULT NOW(),
    concluded boolean NOT NULL DEFAULT FALSE,
    version integer NOT NULL DEFAULT 1
);