import React from "react";
import ConfigAgentView from './ConfigAgentView'
import ConfigAgentEditor from './ConfigAgentEditor'
import AgentTopManager from "./AgentTopManager";

const AgentConfigation = ({ sendMessage, lastResponse, source_key, config }) => {
  const handleSendMessage = (data) => {
    sendMessage({
      data: data,
      to: source_key,
      index: data.index
    });
  };

  const onSaveHandle = (new_config) => {
    sendMessage({
      data: {
        command: "set_config",
        data: new_config,  
      },
      to: source_key,
    });
    console.log(new_config)
  }

  return (
    <div>
        <AgentTopManager lastResponse={lastResponse} sendMessage={handleSendMessage}/>
        <ConfigAgentView config={config}/>
        <ConfigAgentEditor config={config} onSave={onSaveHandle}/>
    </div>
  );
};

export default AgentConfigation;
