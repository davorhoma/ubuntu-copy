ARG VERSION=1.22.1

FROM golang:$VERSION

WORKDIR /docker-go

COPY go.mod go.sum .

RUN go mod download

COPY . .

ENTRYPOINT ["go", "run", "main.go"]

ENV PORT=4000

EXPOSE $PORT
