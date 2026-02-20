FROM python:3.12-alpine
WORKDIR /app
RUN pip install flask
COPY . /app
ENTRYPOINT ["python"]
CMD ["server.py"]