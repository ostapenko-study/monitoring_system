import React, { useState } from 'react';

const containerStyle = {
  padding: '16px',
  backgroundColor: '#f3f4f6',
  borderRadius: '16px',
  boxShadow: '0 2px 8px rgba(0,0,0,0.1)',
  margin: 'auto'
};

const titleStyle = {
  fontSize: '20px',
  fontWeight: 'bold',
  marginBottom: '16px',
  textAlign: 'center'
};

const sectionStyle = {
  marginBottom: '16px'
};

const sectionTitleStyle = {
  fontSize: '18px',
  fontWeight: '600',
  marginBottom: '8px'
};

const inputStyle = {
  width: '100%',
  padding: '8px',
  borderRadius: '8px',
  border: '1px solid #ddd',
  fontSize: '16px'
};

const buttonStyle = {
    padding: '10px 20px',
    backgroundColor: '#4CAF50',
    color: 'white',
    fontSize: '16px',
    border: 'none',
    borderRadius: '8px',
    cursor: 'pointer',
    marginTop: '16px',
    width: 'auto',
    display: 'block',
    marginLeft: 'auto',
    marginRight: 'auto'
  };
const errorStyle = {
  color: 'red',
  fontSize: '14px',
  marginTop: '8px'
};

const ConfigAgentEditor = ({ onSave }) => {
  const [users, setUsers] = useState('');
  const [processes, setProcesses] = useState('');
  const [timeout, setTimeout] = useState('');
  const [error, setError] = useState('');

  const handleSave = () => {
    if (timeout <= 100) {
      setError('Таймаут має бути більше 100!');
      return;
    }
    setError('');
    const usersArray = users.split(',').map(user => user.trim());
    const processesArray = processes.split(',').map(process => process.trim());
    onSave({ users: usersArray, processes: processesArray, timeout: Number(timeout) });
  };

  return (
    <div style={containerStyle}>
      <h2 style={titleStyle}>Змінити конфігурацію</h2>

      <div style={sectionStyle}>
        <label style={sectionTitleStyle}>Користувачі:</label>
        <input
          type="text"
          value={users}
          onChange={(e) => setUsers(e.target.value)}
          style={inputStyle}
          placeholder="Введіть користувачів через кому"
        />
      </div>

      <div style={sectionStyle}>
        <label style={sectionTitleStyle}>Процеси:</label>
        <input
          type="text"
          value={processes}
          onChange={(e) => setProcesses(e.target.value)}
          style={inputStyle}
          placeholder="Введіть процеси через кому"
        />
      </div>

      <div style={sectionStyle}>
        <label style={sectionTitleStyle}>Таймаут:</label>
        <input
          type="number"
          value={timeout}
          onChange={(e) => setTimeout(e.target.value)}
          style={inputStyle}
          placeholder="Таймаут більше 100"
        />
      </div>

      {error && <p style={errorStyle}>{error}</p>}

      <button style={buttonStyle} onClick={handleSave}>Зберегти</button>
    </div>
  );
};

export default ConfigAgentEditor;
