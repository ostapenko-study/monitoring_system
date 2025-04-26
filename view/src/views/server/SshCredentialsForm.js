import React from "react";

import "../../styles/box.css";

const SshCredentialsForm = ({ username, password, onChange }) => {
  return (
    <div className="box">
      <div style={styles.header}>SSH дані</div>
      <label style={styles.label}>
        Користувач:
        <input
          type="text"
          value={username}
          onChange={(e) => onChange({ username: e.target.value, password })}
          style={styles.input}
        />
      </label>
      <label style={styles.label}>
        Пароль:
        <input
          type="password"
          value={password}
          onChange={(e) => onChange({ username, password: e.target.value })}
          style={styles.input}
        />
      </label>
    </div>
  );
};

const styles = {
  container: {
    display: "flex",
    flexDirection: "column",
    gap: "10px",
    marginTop: "15px",
    padding: "15px",
    border: "1px solid #ccc",
    borderRadius: "8px",
    backgroundColor: "#f9f9f9",
  },
  label: {
    fontWeight: "bold",
    display: "flex",
    flexDirection: "column",
  },
  input: {
    padding: "8px",
    borderRadius: "4px",
    border: "1px solid #ccc",
    fontSize: "14px",
    marginTop: "4px",
  },
};

export default SshCredentialsForm;
