import React from "react";

export const NetworkInfo = ({ data }) => {
  const { ip, mac, name, netmask, addresses } = data;

  return (
    <div style={styles.wrapper}>
      <h2 style={styles.title}>Інформація про мережу</h2>

      <div style={styles.section}>
        <div><strong>Інтерфейс:</strong> {name}</div>
        <div><strong>IP:</strong> {ip}</div>
        <div><strong>MAC:</strong> {mac}</div>
        <div><strong>Маска:</strong> {netmask}</div>
      </div>

      <div style={styles.section}>
        <h3>Знайдені адреси ({addresses.length}):</h3>
        <ul style={styles.list}>
          {addresses.map((addr, i) => (
            <li key={i} style={addr === ip ? styles.highlight : {}}>
              {addr}
            </li>
          ))}
        </ul>
      </div>
    </div>
  );
};

const styles = {
  wrapper: {
    maxWidth: "600px",
    margin: "2rem auto",
    padding: "1.5rem",
    border: "1px solid #ddd",
    borderRadius: "12px",
    backgroundColor: "#f9f9f9",
    fontFamily: "sans-serif",
  },
  title: {
    fontSize: "1.5rem",
    marginBottom: "1rem",
    color: "#333",
    textAlign: "center",
  },
  section: {
    marginBottom: "1.5rem",
  },
  list: {
    listStyleType: "none",
    paddingLeft: 0,
    columns: 2,
  },
  highlight: {
    backgroundColor: "#d1ecf1",
    padding: "4px 8px",
    borderRadius: "4px",
    fontWeight: "bold",
  },
};

export default NetworkInfo;
