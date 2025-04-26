import React from "react";
import ManagerWrapper from "./ManagerWrapper";
import ProcessTopView from "./ProcessTopView";

const ProcessTopManager = ({ sendMessage, lastResponse, ip }) => {
  const handleSendMessage = ({ index }) => {
    sendMessage({
      command: "get_top_by_ssh",
      data: { ip: ip },
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
          if (!data.top || data.top.length === 0) {
            return <div>Запит (якщо був) повернув пусту відповідь</div>;
          }
          return <ProcessTopView processes={data.top} />;
        }}
    />
  );
};

export default ProcessTopManager;
