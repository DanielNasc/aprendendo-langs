import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';

import { Configs } from './pages/Configs';
import { Main } from './pages/Main';
import { Profile } from './pages/Profile';

export function AppRoutes()
{
    return (
        <Router>
            <Routes>
                <Route path="/" element={<Main />} />
                <Route path="/configs" element={<Configs />} />
                <Route path="/profile" element={<Profile />} />
            </Routes>
        </Router>
    )
}