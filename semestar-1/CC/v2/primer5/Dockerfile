FROM python:3.12-alpine
WORKDIR /app
RUN pip install flask

COPY server.py /app
ENTRYPOINT ["python", "server.py"]