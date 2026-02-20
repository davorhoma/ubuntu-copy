import React from 'react';

import './GoalItem.css';

function GoalItem(props) {
  return <li className="goal-item">{props.text}</li>;
}

export default GoalItem;
