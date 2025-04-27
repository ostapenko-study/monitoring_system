import React, { useState } from "react";
import ManagerWrapper from "./ManagerWrapper";

import "../../styles/box.css";

const SetupDeviceManager = ({ sendMessage, lastResponse, ip }) => {
  const [useProxy, setUseProxy] = useState(false);
  const [useAgent, setUseAgent] = useState(false);
  const [nodeName, setNodeName] = useState("");

  const handleSendMessage = ({ index }) => {
    sendMessage({
      command: "setup_device_by_ssh",
      data: {
        ip: ip,
        proxy: useProxy,
        agent: useAgent,
        name_id: nodeName,
      },
      index: index
    });
  };

  const renderContent = (data) => {

    return (

      <div style={{ margin: "10px" }}>
        {/* <div>
          <label>
            <input
              type="checkbox"
              checked={useProxy}
              onChange={() => setUseProxy(!useProxy)}
            />{" "}
            Використовувати Proxy
          </label>
        </div> */}

        <div>
          <label>
            <input
              type="checkbox"
              checked={useAgent}
              onChange={() => setUseAgent(!useAgent)}
            />{" "}
            Використовувати Agent
          </label>
        </div>

        <div style={{ marginLeft: "24px" }}>
          <label>
            Ім'я вузла:
            <input
              type="text"
              value={nodeName}
              onChange={(e) => setNodeName(e.target.value)}
              placeholder="Введіть ім'я"
              style={{ marginLeft: "10px" }}
            />
          </label>
        </div>

        <div style={{ marginTop: "20px" }}>
          {Object.keys(data).length !== 0 ? (
            <div>{data["isOk"] == true ? "Попередній запит виконано вірно" : data["error"]}</div>
          ) : (
            <div>Запит (якщо був) повернув пусту відповідь</div>
          )}
        </div>
      </div>
    )
  };

  return (
    <ManagerWrapper
      sendMessage={handleSendMessage}
      lastResponse={lastResponse}
      title="Налаштування вузла"
      resultGenerator={renderContent}
    />
  );
};

export default SetupDeviceManager;
