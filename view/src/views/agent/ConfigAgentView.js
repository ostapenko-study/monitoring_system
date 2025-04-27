import React from 'react';

const containerStyle = {
  padding: '16px',
  backgroundColor: '#f3f4f6',
  borderRadius: '16px',
  boxShadow: '0 2px 8px rgba(0,0,0,0.1)'
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
  fontWeight: '600'
};

const listStyle = {
  listStyleType: 'disc',
  paddingLeft: '20px'
};


const ConfigAgentView = ({ config }) => {
  const users = config.users || [];
  const processes = config.processes || [];
  const timeout = config.timeout;

  const renderListOrDash = (items) => {
    if (!items || items.length === 0) {
      return <p>-</p>;
    }

    return (
      <ul style={listStyle}>
        {items.map((item, idx) => (
          <li key={idx}>{item}</li>
        ))}
      </ul>
    );
  };

  return (
    <div style={containerStyle}>
      <h2 style={titleStyle}>Поточна конфігурація</h2>
      <div style={sectionStyle}>
        <h3 style={sectionTitleStyle}>Users:</h3>
        {renderListOrDash(users)}
      </div>

      <div style={sectionStyle}>
        <h3 style={sectionTitleStyle}>Processes:</h3>
        {renderListOrDash(processes)}
      </div>

      <div>
        <h3 style={sectionTitleStyle}>Timeout:</h3>
        <p>{timeout} seconds</p>
      </div>
    </div>
  );
};

export default ConfigAgentView;
