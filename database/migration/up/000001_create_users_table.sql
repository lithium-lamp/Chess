CREATE TABLE IF NOT EXISTS users (
    id serial PRIMARY KEY,
    created_at timestamp(0) with time zone NOT NULL DEFAULT NOW(),
    name text NOT NULL UNIQUE,
    version integer NOT NULL DEFAULT 1
);