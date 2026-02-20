FROM node
WORKDIR /app
COPY package*.json .
RUN npm install
COPY . .

RUN mkdir -p temp feedback

ENTRYPOINT ["node"]
CMD ["server.js"]