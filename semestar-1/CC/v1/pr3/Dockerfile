FROM node
WORKDIR /app
COPY . /app
RUN npm install
EXPOSE 3001
ENTRYPOINT ["node"]
CMD ["server.js"]

# 3: docker run -d --name primer3 -p 3001:3001 primer3
# 4: docker inspect primer3
# 5: docker stats primer3
# 6: docker stop primer3
# 7: docker start primer3
# 8: docker attach primer3
# 9: docker logs primer3