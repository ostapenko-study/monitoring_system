import React from "react";

import NetworkInfo from "./NetworkInfo";

export const NetworkList = ({ items }) => {
  return (
    <div style={styles.listWrapper}>
      <h2 style={styles.title}>Список мережевих інтерфейсів</h2>
      {
        items.map((item, index) => <NetworkInfo data={item}/>)
      }
    </div>
  );
};

const styles = {
  listWrapper: {
    maxWidth: "800px",
    margin: "2rem auto",
    fontFamily: "sans-serif",
  },
  title: {
    fontSize: "1.6rem",
    marginBottom: "1rem",
    textAlign: "center",
  },
  card: {
    padding: "1rem",
    marginBottom: "1.5rem",
    border: "1px solid #ccc",
    borderRadius: "8px",
    background: "#f5f5f5",
  },
  addrList: {
    listStyleType: "none",
    paddingLeft: "1rem",
    columns: 2,
  },
  highlight: {
    backgroundColor: "#d1ecf1",
    padding: "2px 6px",
    borderRadius: "4px",
    fontWeight: "bold",
  },
};

export default NetworkList;
