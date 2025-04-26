import React, { useState, useCallback, useEffect } from 'react';

import SshCredentialsForm from './SshCredentialsForm';
import ProcessTopManager from './ProcessTopManager'
import SetupDeviceManager from './SetupDeviceManager'

const AddressWorkerModal = ({ ip, onClose, sendMessage, lastResponse}) => {

  const [credentials, setCredentials] = useState({ username: "", password: "" });


  const sendMessageWrapper = (pkg) => {
    pkg.data.user = credentials.username
    pkg.data.password = credentials.password
    sendMessage(pkg);
  };

  return (
    <div style={styles.backdrop}>
      <div style={styles.modal}>
        <button style={styles.closeButton} onClick={onClose}>×</button>
        <h2>IP вузла: {ip}</h2>
        <SshCredentialsForm
          username={credentials.username}
          password={credentials.password}
          onChange={setCredentials}
        />
        <ProcessTopManager sendMessage={sendMessageWrapper} lastResponse={lastResponse} ip={ip}/>
        <SetupDeviceManager sendMessage={sendMessageWrapper} lastResponse={lastResponse} ip={ip}/>
      </div>
    </div>
  );

};

const styles = {
  backdrop: {
    position: "fixed",
    top: 0, left: 0, right: 0, bottom: 0,
    backgroundColor: "rgba(0,0,0,0.5)",
    display: "flex",
    alignItems: "center",
    justifyContent: "center",
  },
  modal: {
    position: "relative",
    backgroundColor: "#fff",
    padding: "20px",
    borderRadius: "8px",
    width: "800px",
    maxWidth: "90%",
    overflowY: 'auto',
    maxHeight: "90%",
  },
  closeButton: {
    position: "absolute",
    top: "10px",
    right: "10px",
    background: "transparent",
    border: "none",
    fontSize: "20px",
    cursor: "pointer",
    color: "#555",
    transition: "color 0.2s ease, transform 0.2s ease",
  },
};

export default AddressWorkerModal;
