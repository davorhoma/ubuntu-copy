document.getElementById('loadData').addEventListener('click', function() {
    fetch('http://localhost:4000/')
        .then(response => response.json())
        .then(data => {
            document.getElementById('response').innerHTML = 'Server Response: ' + data.response;
            document.getElementById('displayImage').style.display = 'none';
        })
        .catch(error => console.error('Error:', error));
});


document.getElementById('dontClick').addEventListener('click', function() {
    fetch('http://localhost:4000/helloThere')
    .then(response => response.json())
    .then(data => {
        
            let imgElement = document.getElementById('displayImage');
            imgElement.src = data.response;
            imgElement.style.display = 'block'; // Show the image element
        
    })
    .catch(error => console.error('Error:', error));});
