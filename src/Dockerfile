#---build---
FROM alpine:latest AS builder
# Located in latest workdir `RUN mkdir -p /application/ && cd /application/`
WORKDIR /application/
RUN apk add --no-cache sqlite-dev musl-dev gcc make sqlite
COPY . /application/
RUN make create-db
RUN make refresh-db
RUN make app

#---runtime---
FROM alpine:latest
WORKDIR /usr/local/bin/
RUN apk add --no-cache sqlite-libs sqlite  #runtime lib + CLI
COPY --from=builder /application/app.exe /usr/local/bin/app.exe
RUN mkdir -p /usr/local/bin/database/
COPY --from=builder /application/database/local.db /usr/local/bin/database/local.db

CMD [ "/usr/local/bin/app.exe" ]

