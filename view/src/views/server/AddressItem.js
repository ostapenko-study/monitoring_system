import React from "react";

const AddressItem = ({ address, isHost, onOpenAddressWorker}) => {
  return (
    <li style={styles.item}>
      <span style={isHost ? styles.host : null}>{address}</span>
      {!isHost && (
        <div>
          <button style={styles.button} onClick={() => onOpenAddressWorker(address)}>
            Працювати з вузлом
          </button>
        </div>
      )}
    </li>
  );
};

const styles = {
  item: {
    display: "flex",
    alignItems: "center",
    justifyContent: "space-between",
    padding: "4px 0",
    borderBottom: "1px dashed #ccc",
  },
  host: {
    fontWeight: "bold",
    color: "#28a745",
  },
  button: {
    backgroundColor: "#007bff",
    color: "#fff",
    border: "none",
    padding: "4px 10px",
    borderRadius: "4px",
    cursor: "pointer",
  },
};

export default AddressItem;
