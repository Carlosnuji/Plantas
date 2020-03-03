--
-- PostgreSQL database dump
--

-- Dumped from database version 10.10
-- Dumped by pg_dump version 10.10

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


--
-- Name: pgcrypto; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS pgcrypto WITH SCHEMA public;


--
-- Name: EXTENSION pgcrypto; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION pgcrypto IS 'cryptographic functions';


SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: queja; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.queja (
    idqueja integer NOT NULL,
    idusuario integer NOT NULL,
    queja text NOT NULL
);


ALTER TABLE public.queja OWNER TO postgres;

--
-- Name: Quejas_idqueja_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Quejas_idqueja_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."Quejas_idqueja_seq" OWNER TO postgres;

--
-- Name: Quejas_idqueja_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Quejas_idqueja_seq" OWNED BY public.queja.idqueja;


--
-- Name: envio_email; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.envio_email (
    idenvio integer NOT NULL,
    idusuario integer,
    date date DEFAULT CURRENT_DATE
);


ALTER TABLE public.envio_email OWNER TO postgres;

--
-- Name: envio_email_idenvio_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.envio_email_idenvio_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.envio_email_idenvio_seq OWNER TO postgres;

--
-- Name: envio_email_idenvio_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.envio_email_idenvio_seq OWNED BY public.envio_email.idenvio;


--
-- Name: favorito; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.favorito (
    idfavorito integer NOT NULL,
    idusuario integer,
    idplanta integer
);


ALTER TABLE public.favorito OWNER TO postgres;

--
-- Name: favorito_idfavorito_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.favorito_idfavorito_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.favorito_idfavorito_seq OWNER TO postgres;

--
-- Name: favorito_idfavorito_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.favorito_idfavorito_seq OWNED BY public.favorito.idfavorito;


--
-- Name: planta; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.planta (
    idplanta integer NOT NULL,
    nombre character varying(50) NOT NULL,
    nombrecientifico character varying(50) NOT NULL,
    descripcion character varying(50) NOT NULL,
    imagen bytea
);


ALTER TABLE public.planta OWNER TO postgres;

--
-- Name: planta_idplanta_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.planta_idplanta_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.planta_idplanta_seq OWNER TO postgres;

--
-- Name: planta_idplanta_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.planta_idplanta_seq OWNED BY public.planta.idplanta;


--
-- Name: token; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.token (
    idtoken integer NOT NULL,
    uuid text,
    idusuario integer,
    date date DEFAULT CURRENT_DATE
);


ALTER TABLE public.token OWNER TO postgres;

--
-- Name: token_idtoken_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.token_idtoken_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.token_idtoken_seq OWNER TO postgres;

--
-- Name: token_idtoken_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.token_idtoken_seq OWNED BY public.token.idtoken;


--
-- Name: usuario; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.usuario (
    idusuario integer NOT NULL,
    nombre character varying(50) NOT NULL,
    password text NOT NULL,
    email character varying(100) NOT NULL,
    status integer DEFAULT 0
);


ALTER TABLE public.usuario OWNER TO postgres;

--
-- Name: usuario_idusuario_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.usuario_idusuario_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.usuario_idusuario_seq OWNER TO postgres;

--
-- Name: usuario_idusuario_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.usuario_idusuario_seq OWNED BY public.usuario.idusuario;


--
-- Name: envio_email idenvio; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.envio_email ALTER COLUMN idenvio SET DEFAULT nextval('public.envio_email_idenvio_seq'::regclass);


--
-- Name: favorito idfavorito; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.favorito ALTER COLUMN idfavorito SET DEFAULT nextval('public.favorito_idfavorito_seq'::regclass);


--
-- Name: planta idplanta; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.planta ALTER COLUMN idplanta SET DEFAULT nextval('public.planta_idplanta_seq'::regclass);


--
-- Name: queja idqueja; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.queja ALTER COLUMN idqueja SET DEFAULT nextval('public."Quejas_idqueja_seq"'::regclass);


--
-- Name: token idtoken; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.token ALTER COLUMN idtoken SET DEFAULT nextval('public.token_idtoken_seq'::regclass);


--
-- Name: usuario idusuario; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.usuario ALTER COLUMN idusuario SET DEFAULT nextval('public.usuario_idusuario_seq'::regclass);


--
-- Data for Name: envio_email; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.envio_email (idenvio, idusuario, date) FROM stdin;
\.


--
-- Data for Name: favorito; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.favorito (idfavorito, idusuario, idplanta) FROM stdin;
4	50	1
6	50	2
27	48	1
\.


--
-- Data for Name: planta; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.planta (idplanta, nombre, nombrecientifico, descripcion, imagen) FROM stdin;
1	planta1	plantis1	descripcion	\\x2f686f6d652f7573756172696f2f50726f796563746f506c616e7461732f536572766572506c616e7461732f5765625573756172696f2f696d672f6172626f6c2e6a7067
2	planta2	plantis2	una descripcion	\\x2f686f6d652f7573756172696f2f50726f796563746f506c616e7461732f536572766572506c616e7461732f5765625573756172696f2f696d672f6172626f6c2e6a7067
\.


--
-- Data for Name: queja; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.queja (idqueja, idusuario, queja) FROM stdin;
3	48	No se calla
4	48	Es una mierda
5	48	Va muy lento
6	48	Bozhena no se calla
7	48	Bozhena no se calla
8	48	Bozhena no se calla
9	48	Bozhena no se calla
10	48	Bozhena no se calla
\.


--
-- Data for Name: token; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.token (idtoken, uuid, idusuario, date) FROM stdin;
1	{a97f3f06-63c5-40de-b198-8bab0b48db9a}	48	2020-02-20
\.


--
-- Data for Name: usuario; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.usuario (idusuario, nombre, password, email, status) FROM stdin;
50	Javier	$2a$06$ikD/1.vKO1G6UkQ5HAXa2.TBb7/kal.Mg.GmBcA39ZLZSehPjbbNa	javier@gmail.com	0
51	Laura	$2a$06$MrgvASR94mDxV8mcKxkw.uL57TpV1KnraYV.l/dIBOjZojmdHvXde	laura@gmail.com	0
48	Carlos	$2a$06$4TkaGGjMSp.Sjo6Vl1Ou3e07wu9SaHXoDreBQ.IW65aqU6Jilw752	carlos@gmail.com	1
49	Prueba	$2a$06$rKMPNj2.NXY4bme0utOnyudpDIrezLwEe2xS/Dnz/rq3Bt4oyaKyG	prueba@gmail.com	0
\.


--
-- Name: Quejas_idqueja_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Quejas_idqueja_seq"', 11, true);


--
-- Name: envio_email_idenvio_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.envio_email_idenvio_seq', 1, false);


--
-- Name: favorito_idfavorito_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.favorito_idfavorito_seq', 27, true);


--
-- Name: planta_idplanta_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.planta_idplanta_seq', 4, true);


--
-- Name: token_idtoken_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.token_idtoken_seq', 42, true);


--
-- Name: usuario_idusuario_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.usuario_idusuario_seq', 101, true);


--
-- Name: queja Quejas_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.queja
    ADD CONSTRAINT "Quejas_pkey" PRIMARY KEY (idqueja);


--
-- Name: favorito favorito_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.favorito
    ADD CONSTRAINT favorito_pkey PRIMARY KEY (idfavorito);


--
-- Name: planta planta_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.planta
    ADD CONSTRAINT planta_pkey PRIMARY KEY (idplanta);


--
-- Name: usuario usuario_email_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.usuario
    ADD CONSTRAINT usuario_email_key UNIQUE (email);


--
-- Name: usuario usuario_nombre_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.usuario
    ADD CONSTRAINT usuario_nombre_key UNIQUE (nombre);


--
-- Name: usuario usuario_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.usuario
    ADD CONSTRAINT usuario_pkey PRIMARY KEY (idusuario);


--
-- Name: envio_email envio_email_idusuario_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.envio_email
    ADD CONSTRAINT envio_email_idusuario_fkey FOREIGN KEY (idusuario) REFERENCES public.usuario(idusuario);


--
-- Name: favorito favorito_idplanta_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.favorito
    ADD CONSTRAINT favorito_idplanta_fkey FOREIGN KEY (idplanta) REFERENCES public.planta(idplanta);


--
-- Name: favorito favorito_idusuario_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.favorito
    ADD CONSTRAINT favorito_idusuario_fkey FOREIGN KEY (idusuario) REFERENCES public.usuario(idusuario);


--
-- Name: queja queja_idusuario_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.queja
    ADD CONSTRAINT queja_idusuario_fkey FOREIGN KEY (idusuario) REFERENCES public.usuario(idusuario) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- Name: token token_idusuario_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.token
    ADD CONSTRAINT token_idusuario_fkey FOREIGN KEY (idusuario) REFERENCES public.usuario(idusuario);


--
-- PostgreSQL database dump complete
--

