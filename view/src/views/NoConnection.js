export const NoConnection = ({ url }) => {
    return (
      <div style={styles.container}>
        <div style={styles.box}>
          <h2 style={styles.title}>Сервер недоступний</h2>
          <p style={styles.text}>
            Не вдалося з'єднатися з <span style={styles.url}>{url}</span>
          </p>
        </div>
      </div>
    );
  };
  
  const styles = {
    container: {
      height: "100vh",
      width: "100vw",
      backgroundColor: "#fff0f0",
      display: "flex",
      alignItems: "center",
      justifyContent: "center",
    },
    box: {
      textAlign: "center",
      padding: "2rem",
      border: "1px solid #ffcccc",
      borderRadius: "12px",
      backgroundColor: "#ffe5e5",
      boxShadow: "0 4px 12px rgba(0,0,0,0.1)",
    },
    title: {
      fontSize: "1.8rem",
      color: "#cc0000",
      marginBottom: "0.5rem",
    },
    text: {
      fontSize: "1rem",
      color: "#990000",
    },
    url: {
      fontFamily: "monospace",
      fontWeight: "bold",
    },
  };

export default NoConnection;