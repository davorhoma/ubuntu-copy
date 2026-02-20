FROM alpine
WORKDIR /app
COPY test.txt .
COPY test.txt /app
# COPY test.txt app # failed
# COPY test.txt app/ # test.txt smesta na putanju /app/app
COPY test.txt /app/
# ENTRYPOINT ["cat"]
CMD ["test.txt"]