
import SystemView from './system/SystemView'
import AppView from './AppView';
import UserView from './UserView';
import ExpandedForm from './ExpandedForm';
import AgentConfigation from './agent/AgentConfiguration'

export const SourceView = ({sendMessage, lastResponse, source_key, title, data}) => {

    const totals = {
        cpu: Object.values(data.system.cpu).reduce((total, currentValue) => total + currentValue, 0), 
        memory: data.system.memory.main.total,
        swap: data.system.memory.swap.total,
    }

    const processes_items = data.processes.map((process, id) => 
        <AppView key={process.name} data={process} totals={totals}/>
    )

    const users_items = data.users.map((user, id) => 
        <UserView key={user.name} data={user} totals={totals}/>
    )

    return (
        <ExpandedForm title={title}>
            <ExpandedForm title={"Конфігурація"}>
                <AgentConfigation 
                    sendMessage={sendMessage}
                    lastResponse={lastResponse}
                    source_key={source_key}
                    config={data.config}
                />
            </ExpandedForm>
            <ExpandedForm title={"Система"}>
                <SystemView data={data.system} totals={totals} />
            </ExpandedForm>
            <ExpandedForm title={"Користувачі"}>
                {users_items}
            </ExpandedForm>
            <ExpandedForm title={"Процеси"}>
                {processes_items}
            </ExpandedForm>
        </ExpandedForm>
    );
};

export default SourceView;