import React from "react";
import ManagerWrapper from "../ManagerWrapper";
import ProcessTopView from "../ProcessTopView";

const AgentTopManager = ({ sendMessage, lastResponse }) => {
  const handleSendMessage = ({ index }) => {
    sendMessage({
      command: "get_top",
      index: index
    });
  };

  return (
    <ManagerWrapper
      sendMessage={handleSendMessage}
      lastResponse={lastResponse}
      title="Перелік процесів"
      resultGenerator = {
        (data) => {
          if (!data.data.top || data.data.top.length === 0) {
            return <div>Запит (якщо був) повернув пусту відповідь</div>;
          }
          return <ProcessTopView processes={data.data.top} />;
        }}
    />
  );
};

export default AgentTopManager;
