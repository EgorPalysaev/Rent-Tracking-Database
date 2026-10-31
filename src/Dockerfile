FROM cleanstart/sqlite3:latest
FROM mcp/sqlite:latest
FROM athenaos/base:latest
FROM gcc

WORKDIR /rentrack

COPY . /rentrack

RUN make

CMD [ "./app" ]
