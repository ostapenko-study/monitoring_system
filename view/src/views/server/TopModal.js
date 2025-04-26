import React from "react";

const TopModal = ({ ip, onClose }) => {
  return (
    <div style={styles.backdrop}>
      <div style={styles.modal}>
        <h2>Top: {ip}</h2>
        {/* тут буде твоя логіка */}
        <button onClick={onClose}>Закрити</button>
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
    backgroundColor: "#fff",
    padding: "20px",
    borderRadius: "8px",
    width: "400px",
    maxWidth: "90%",
  },
};

export default TopModal;
