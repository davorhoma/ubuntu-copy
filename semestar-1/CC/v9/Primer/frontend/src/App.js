import React, { useState, useEffect, useCallback } from 'react';

import './App.css';
import TaskList from './components/TaskList';
import NewTask from './components/NewTask';

function App() {
  const [tasks, setTasks] = useState([]);

const fetchTasks = useCallback(() => {
  fetch('/api/tasks', {
    headers: { Authorization: 'Bearer abc' },
  })
    .then(async (response) => {
      // pokušaj da parsiraš JSON, ali nemoj da padne aplikacija ako nije JSON
      const data = await response.json().catch(() => null);

      if (!response.ok) {
        throw new Error(data?.message || `Request failed: ${response.status}`);
      }

      return data;
    })
    .then((data) => {
      // garantuj niz
      setTasks(Array.isArray(data?.tasks) ? data.tasks : []);
    })
    .catch((err) => {
      console.error(err);
      setTasks([]); // da TaskList ne puca
      // opciono: setError(err.message)
    });
}, []);


  useEffect(
    function () {
      fetchTasks();
    },
    [fetchTasks]
  );

  function addTaskHandler(task) {
    fetch('/api/tasks', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
        Authorization: 'Bearer abc',
      },
      body: JSON.stringify(task),
    })
      .then(function (response) {
        console.log(response);
        return response.json();
      })
      .then(function (resData) {
        console.log(resData);
      });
  }

  return (
    <div className='App'>
      <section>
        <NewTask onAddTask={addTaskHandler} />
      </section>
      <section>
        <button onClick={fetchTasks}>Fetch Tasks</button>
        <TaskList tasks={tasks} />
      </section>
    </div>
  );
}

export default App;
