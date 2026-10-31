FROM cleanstart/sqlite3:latest
FROM mcp/sqlite:latest
FROM athenaos/base:latest
FROM gcc

WORKDIR /application

COPY . /application

RUN make app

CMD [ "./app" ]
