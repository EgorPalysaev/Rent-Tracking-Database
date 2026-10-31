FROM cleanstart/sqlite3:latest
FROM mcp/sqlite:latest
FROM athenaos/base:latest
FROM gcc

WORKDIR /app

COPY . /app

RUN make app

CMD [ "./app" ]
